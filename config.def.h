/*    ___________      __.___  __:w_______ _________   _____      _____    _______    _______       */
/*   /   _____/  \    /  \   |/   _____//   _____/  /     \    /  _  \   \      \   \      \      */
/*   \_____  \\   \/\/   /   |\_____  \ \_____  \  /  \ /  \  /  /_\  \  /   |   \  /   |   \     */
/*   /        \\        /|   |/        \/        \/    Y    \/    |    \/    |    \/    |    \    */
/*  /_______  / \__/\  / |___/_______  /_______  /\____|__  /\____|__  /\____|__  /\____|__  /    */
/*          \/       \/              \/        \/         \/         \/         \/         \/     */
/*                                                                                                */

/*  ##########################################################################################    */

/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* Multimedia Keys for Volume */
static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%",     NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%",     NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL };

/* Multimedia Keys for Control */
static const char *medplaypausecmd[]     = { "playerctl", "play-pause", NULL };
static const char *mednextcmd[]          = { "playerctl", "next", NULL };
static const char *medprevcmd[]          = { "playerctl", "previous", NULL };
static const char *medstopcmd[]          = { "playerctl", "stop", NULL };

/* Settings for Borders and Bar */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

/* Settings for Fonts */
static const char *fonts[]          = { "NTR:size=12:antialias=true:autohint=true", "FontAwesome:size=12:antialias=true:autohint=true" };
static const char dmenufont[]       = "NTR:size=12:antialias=true:autohint=true";

/* Color Settings */
static const char col_1[]       = "#ffffff";
static const char col_2[]       = "#444444";
static const char col_3[]       = "#4f4f4f";
static const char col_4[]       = "#000000";
static const char col_5[]       = "#8DB8E8";
static const char *colors[][3]      = {
	/*    		          fg		         bg		         border   */
	[SchemeNorm] = {	col_3, 			col_1, 			 col_2 },
	[SchemeSel]  = { 	col_4,			col_5,			 col_5 },
};

/* tagging */
static const char *tags[] = { " ??? ", " ??? ", " ??? ", " ??? ", " ??? ", " ??? ", " ??? ", " ??? ", " ??? " };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 1,       0,           -1 },
	{ "discord",  NULL,       NULL,	      1 << 3,       0,           -1 },
	{ "Lutris",   NULL,       NULL,       1 << 4,       0,           -1 },

};

/* layout(s) */
static const float mfact     = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[ ??? ]",      tile },    /* first entry is default */
	{ "[ ??? ]",      NULL },    /* no layout function means floating behavior */
	{ "[ ??? ]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define PrintScreenDWM	    0x0000ff61


/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = 	    { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_1, "-nf", col_3, "-sb", col_5, "-sf", col_4, NULL };
static const char *termcmd[]  =             { "alacritty", NULL };
static const char *cmdprintscreen[]  =      { "scrot", "-d3", "/home/vale/Pictures/Screenshots/%Y-%m-%d-%s_$wx$h.jpg", NULL };
static const char *flameshotcmd[] =         { "flameshot", "gui", NULL }; 
static const char *lockcmd[] =              { "betterlockscreen", "-l", "dimblur", "0.6", NULL };
static const char *roficmd[] =              { "rofi", "-show", "run", "drun", "ssh", "-font Hasklug Nerd Font 11", NULL };

static Key keys[] = {
	/* modifier                     key        		function        argument */

/* Spawns from Terminal, DMenu and Rofi */
	{ MODKEY|ShiftMask,             XK_Return, 		spawn,          {.v = termcmd } },
	{ ControlMask,                  XK_Return,              spawn,          {.v = dmenucmd } },
	{ ControlMask|ShiftMask,        XK_Return,              spawn,          {.v = roficmd } },

/* Movment */	
	{ MODKEY,                       XK_b,      		togglebar,      {0} },
	{ MODKEY,                       XK_j,      		focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      		focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      		incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      		incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      		setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      		setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, 		zoom,           {0} },
	{ MODKEY,                       XK_Tab,    		view,           {0} },
	{ MODKEY|ShiftMask,             XK_e,      		killclient,     {0} },
	{ MODKEY,                       XK_t,      		setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      		setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      		setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  		setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  		togglefloating, {0} },
	{ MODKEY,                       XK_0,      		view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      		tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  		focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, 		focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  		tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, 		tagmon,         {.i = +1 } },

/* Tag Switching */
	TAGKEYS(                        XK_1,                      		0)
	TAGKEYS(                        XK_2,                      		1)
	TAGKEYS(                        XK_3,                      		2)
	TAGKEYS(                        XK_4,                      		3)
	TAGKEYS(                        XK_5,                      		4)
	TAGKEYS(                        XK_6,                      		5)
	TAGKEYS(                        XK_7,                      		6)
	TAGKEYS(                        XK_8,                      		7)
	TAGKEYS(                        XK_9,                      		8)
	{ MODKEY|ShiftMask,             XK_F12,      		quit,  		{0} },


/* Multimedia Keys */

    	{ 0,                      XF86XK_AudioLowerVolume,      spawn,          {.v = downvol } },
	{ 0,                      XF86XK_AudioMute,             spawn,          {.v = mutevol } },
    	{ 0,                      XF86XK_AudioRaiseVolume,      spawn,          {.v = upvol   } },
    	{ 0,                      XF86XK_AudioPlay,             spawn,          {.v = medplaypausecmd } },
    	{ 0,                      XF86XK_AudioNext,             spawn,          {.v = mednextcmd } },
    	{ 0,                      XF86XK_AudioPrev,             spawn,          {.v = medprevcmd } },
    	{ 0,                      XF86XK_AudioStop,             spawn,          {.v = medstopcmd } },

/* Screenshot Keys */

	{ 0,                      PrintScreenDWM,               spawn,          {.v = cmdprintscreen } },
	{ MODKEY|ShiftMask,             XK_p,                   spawn,          {.v = flameshotcmd } },

/* Lockscreen */
	{ MODKEY|ShiftMask,             XK_l,                   spawn,          {.v = lockcmd } },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


