#ifdef USE_XINPUT_DEVICES

/*
 * X-Mame XInput trackball code
 *
 */
#include "xmame.h"
#include "devices.h"
#include "../video-drivers/x11.h"

#include "XInputDevices.h"


static XInputDeviceData XIdevices[XINPUT_MAX_NUM_DEVICES];

/* options for XInput-devices */
struct rc_option XInputDevices_opts[] = {
   { "XInput-trackball1",	"XItb1",	rc_string,
     &XIdevices[XINPUT_MOUSE_0].deviceName,
     NULL,	1,		0,	NULL,
     "Device name for trackball of player 1 (see XInput)" },
   { "XInput-trackball2",	"XItb2",	rc_string,
     &XIdevices[XINPUT_MOUSE_1].deviceName,
     NULL,	1,		0,	NULL,
     "Device name for trackball of player 2 (see XInput)" },
   { "XInput-trackball3",	"XItb3",	rc_string,
     &XIdevices[XINPUT_MOUSE_2].deviceName,
     NULL,	1,		0,	NULL,
     "Device name for trackball of player 3 (see XInput)" },
   { "XInput-trackball4",	"XItb4",	rc_string,
     &XIdevices[XINPUT_MOUSE_3].deviceName,
     NULL,	1,		0,	NULL,
     "Device name for trackball of player 4 (see XInput)" },
   { NULL,		NULL,			rc_end,		NULL,
     NULL,		0,			0,		NULL,
     NULL }
};

/* reset XInput-Event types */
#define INVALID_EVENT_TYPE	-1
static int           motion_type = INVALID_EVENT_TYPE;
static int           button_press_type = INVALID_EVENT_TYPE;
static int           button_release_type = INVALID_EVENT_TYPE;
static int           key_press_type = INVALID_EVENT_TYPE;
static int           key_release_type = INVALID_EVENT_TYPE;
static int           proximity_in_type = INVALID_EVENT_TYPE;
static int           proximity_out_type = INVALID_EVENT_TYPE;

/* reset XInput-struct */
void
XInput_trackballs_reset()
{
  int i;
  for(i=0;i<XINPUT_MAX_NUM_DEVICES;++i) {
    XIdevices[i].mameDevice=XMAME_NULLDEVICE;
    XIdevices[i].deviceName=NULL;
    XIdevices[i].info=NULL;
    XIdevices[i].neverMoved=1;
  }
}

/* prototypes */
/* these two functions were taken from the source of the program 'xinput',
   available at ftp://xxx.xxx.xxx */
static XDeviceInfo*
find_device_info(Display *display, char *name, Bool only_extended);
static int
register_events(int player_id, Display *dpy, XDeviceInfo *info, char *dev_name);


/* initializes XInput devices */
void
XInputDevices_init(void)
{
  int i,j,k;
  XDeviceInfoPtr list;

  fprintf(stderr_file, "XInput: Initialization...\n");

  if (!XQueryExtension(display,"XInputExtension",&i,&j,&k)) {
    fprintf(stderr_file,"XInput: Your Xserver doesn't support XInput Extensions\n");
    return;
  }

  /* parse all devicenames */
  for(i=0;i<XINPUT_MAX_NUM_DEVICES;++i) {
    if (XIdevices[i].deviceName) {
      /* if not NULL, check for an existing device */
      XIdevices[i].info=find_device_info(display,XIdevices[i].deviceName,True);
      if (! XIdevices[i].info) {
	fprintf(stderr_file,"XInput: Unable to find device `%s'. Ignoring it!\n",
		XIdevices[i].deviceName);
	XIdevices[i].deviceName=NULL;
      } else {
	/* ok, found a device, now register device for motion events */
	if (i < XINPUT_JOYSTICK_1) {
	  XIdevices[i].mameDevice=XMAME_TRACKBALL;
	} else {
	  /* prepared for XInput-Joysticks
	  XIdevices[i].mameDevice=XMAME_JOYSTICK;
	  */
	}
	if (! register_events(i, display,XIdevices[i].info,XIdevices[i].deviceName)) {
	  fprintf(stderr_file,"XInput: Couldn't register device `%s' for events. Ignoring it\n",
		  XIdevices[i].deviceName);
	  XIdevices[i].deviceName=NULL;
	}
      }
    }
  }

  /* if core pointer is used as trackball and a XInput device is also defined for player 1
     ignore core pointer */
  if (XIdevices[XINPUT_MOUSE_0].deviceName && use_mouse) {
    fprintf(stderr_file,"XInput: Device `%s' takes precedence over core pointer for player 1\n",
	    XIdevices[XINPUT_MOUSE_0].deviceName);
    use_mouse = 0;
  }

}

/* Process events generated by XInput-devices. For now, just trackballs are supported */
int
XInputProcessEvent(XEvent *ev)
{
  int i;

  if (ev->type == motion_type) {
    XDeviceMotionEvent *motion=(XDeviceMotionEvent *) ev;

    for(i = 0; i < MOUSE; i++)
      if (XIdevices[i].deviceName && motion->deviceid == XIdevices[i].info->id)
	  break;

    if (i == MOUSE)
	return 0;

    if (XIdevices[i].neverMoved) {
	XIdevices[i].neverMoved=0;
	XIdevices[i].previousValue[0] = motion->axis_data[0];
	XIdevices[i].previousValue[1] = motion->axis_data[1];
    }

    mouse_data[i].deltas[0] += motion->axis_data[0] - XIdevices[i].previousValue[0];
    mouse_data[i].deltas[1] += motion->axis_data[1] - XIdevices[i].previousValue[1];


    XIdevices[i].previousValue[0] = motion->axis_data[0];
    XIdevices[i].previousValue[1] = motion->axis_data[1];

    return 1;
  } else if (ev->type == button_press_type || ev->type == button_release_type) {
    XDeviceButtonEvent *button = (XDeviceButtonEvent *)ev;

    for(i = 0; i < MOUSE; i++)
	if (XIdevices[i].deviceName && button->deviceid == XIdevices[i].info->id)
	    break;

    if (i == MOUSE)
	return 0;

    /* fprintf(stderr_file, "XInput: Player %d: Button %d %s\n",
	    i + 1, button->button, button->state ? "released" : "pressed"); */

    mouse_data[i].buttons[button->button - 1] = (ev->type == button_press_type) ? 1 : 0;

    return 1;
  }

  return 0;
}

/* <jake> */
/* call from osd_trak_read for polling trackballs */
void
XInputPollDevices(int player, int *deltax, int *deltay)
{
	int i=player;
	if (player < MOUSE && XIdevices[player].deviceName) {
		*deltax=mouse_data[player].deltas[0];
		*deltay=mouse_data[player].deltas[1];
		mouse_data[player].deltas[0] = 0;
		mouse_data[player].deltas[1] = 0;
	} else {
		*deltax=0;
		*deltay=0;
	}
}
/* </jake> */

/* this piece of code was taken from package xinput-1.12 */
static XDeviceInfo*
find_device_info(Display	*display,
		 char		*name,
		 Bool		only_extended)
{
    XDeviceInfo	*devices;
    int		loop;
    int		num_devices;
    int		len = strlen(name);
    Bool	is_id = True;
    XID		id = 0;

    for(loop=0; loop<len; loop++) {
	if (!isdigit(name[loop])) {
	    is_id = False;
	    break;
	}
    }

    if (is_id) {
	id = atoi(name);
    }

    devices = XListInputDevices(display, &num_devices);

    for(loop=0; loop<num_devices; loop++) {
	if ((!only_extended || (devices[loop].use == IsXExtensionDevice)) &&
	    ((!is_id && strcmp(devices[loop].name, name) == 0) ||
	     (is_id && devices[loop].id == id))) {
	    return &devices[loop];
	}
    }
    return NULL;
}

/* this piece of code was taken from package xinput-1.12 */
static int
register_events(int		player_id,
		Display		*dpy,
		XDeviceInfo	*info,
		char		*dev_name)
{
    int			number = 0;	/* number of events registered */
    XEventClass		event_list[7];
    int			i;
    XAnyClassPtr	any;
    XDevice		*device;
    Window		root_win;
    unsigned long	screen;
    XInputClassInfo	*ip;
    XButtonInfoPtr      binfo;
    XValuatorInfoPtr    vinfo;

    screen = DefaultScreen(dpy);
    root_win = RootWindow(dpy, screen);

    device = XOpenDevice(dpy, info->id);

    if (!device) {
	fprintf(stderr_file, "XInput: Unable to open XInput device `%s'\n", dev_name);
	return 0;
    }

    fprintf(stderr_file, "XInput: Player %d using Device `%s'", player_id + 1, dev_name);
    
    if (device->num_classes > 0) {
	any = (XAnyClassPtr)(info->inputclassinfo);

	for (ip = device->classes, i=0; i<info->num_classes; ip++, i++) {
	    switch (ip->input_class) {
	    case KeyClass:
		DeviceKeyPress(device, key_press_type, event_list[number]); number++;
		DeviceKeyRelease(device, key_release_type, event_list[number]); number++;
		break;

	    case ButtonClass:
		binfo = (XButtonInfoPtr) any;
		DeviceButtonPress(device, button_press_type, event_list[number]); number++;
		DeviceButtonRelease(device, button_release_type, event_list[number]); number++;
		fprintf(stderr_file, ", %d buttons", binfo->num_buttons);
		break;

	    case ValuatorClass:
		vinfo=(XValuatorInfoPtr) any;
		DeviceMotionNotify(device, motion_type, event_list[number]); number++;
		fprintf(stderr_file, ", %d axis", vinfo->num_axes);
		break;

	    default:
		break;
	    }
	    any = (XAnyClassPtr) ((char *) any+any->length);
	}

	if (XSelectExtensionEvent(dpy, root_win, event_list, number)) {
	    fprintf(stderr_file, ": Could not select extended events, not using");
	    number = 0;
	}
    } else
	fprintf(stderr_file, " contains no classes, not using");

    fprintf(stderr_file, "\n");

    return number;
}

#endif /* USE_XINPUT_DEVICES */
