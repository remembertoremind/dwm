/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 20;       /* gaps between windows */
static const unsigned int snap      = 5;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "xos4 Terminus:size=9" };
static const char dmenufont[]       = "xos4 Terminus:size=9";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                        instance    title       tags mask     isfloating   monitor */
	{ NULL,          		NULL,       "mpv",     ~0,            1,           -1 },
	{ "Notes",          		NULL,       NULL,      ~0,            1,           -1 },
	{ "qutebrowser", 		NULL,       NULL,       1,            0,           -1 },
	{ "Emacs",      	 	NULL,       NULL,       1 << 1,       0,           -1 },
	{ "Ncmpcpp",      	 	NULL,       NULL,       1 << 2,       0,           -1 },
	{ "Newsboat",      	 	NULL,       NULL,       1 << 2,       0,           -1 },
	{ "Nnn",      	 	        NULL,       NULL,       1 << 3,       0,           -1 },
	{ "Neomutt",      	 	NULL,       NULL,       1 << 4,       0,           -1 },
	{ "Franz", 	 		NULL,       NULL,       1 << 4,       0,           -1 },
	{ "Microsoft Teams - Preview",  NULL,       NULL,       1 << 4,       0,           -1 },
	{ "Steam", 	 		NULL,       NULL,       1 << 5,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
/*static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };*/
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-b", "-l", "15", NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
  /*light*/
        { MODKEY,                       XK_e,      spawn,          SHCMD("light -A 10") },
        { MODKEY,                       XK_d,      spawn,          SHCMD("light -U 10") },
        { MODKEY|ShiftMask,             XK_e,      spawn,          SHCMD("light -S 100") },
        { MODKEY|ShiftMask,             XK_d,      spawn,          SHCMD("light -S 2") },
	
  /*Sound*/
        { MODKEY,                       XK_q,      spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +10%") },
        { MODKEY,                       XK_a,      spawn,          SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle") },
        { MODKEY,                       XK_z,      spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -10%") },

  /*mpv*/
        { MODKEY|ShiftMask,             XK_q,      spawn,          SHCMD("control_mpv up") },
        { MODKEY|ShiftMask,             XK_a,      spawn,          SHCMD("control_mpv mute") },
        { MODKEY|ShiftMask,             XK_z,      spawn,          SHCMD("control_mpv down") },

  /*mpc*/
        { MODKEY,                       XK_w,      spawn,          SHCMD("mpc volume +10") },
        { MODKEY,                       XK_s,      spawn,          SHCMD("mpc toggle") },
        { MODKEY,                       XK_x,      spawn,          SHCMD("mpc volume -10") },
        { MODKEY|ShiftMask,             XK_w,      spawn,          SHCMD("mpc prev") },
        { MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("mpc toggle") },
        { MODKEY|ShiftMask,             XK_x,      spawn,          SHCMD("mpc next") },

  /*Scripts*/
	{ MODKEY,             		XK_t,      spawn,          SHCMD("tv-channels") },
	{ MODKEY|ShiftMask,    		XK_Delete, spawn,          SHCMD("slock") },
	{ MODKEY,          		XK_Print,  spawn,          SHCMD("maimshot") },

  /*Software*/
	{ MODKEY,            		XK_m,      spawn,          SHCMD("st -c Neomutt -e neomutt") },
	{ MODKEY|ShiftMask,   		XK_n,      spawn,          SHCMD("st -c Newsboat -e newsboat") },
	{ MODKEY,            		XK_n,      spawn,          SHCMD("st -c Ncmpcpp -e ncmpcpp") },
	{ MODKEY,            		XK_r,      spawn,          SHCMD("wallpaper -r") },
	{ MODKEY|ShiftMask,   		XK_r,      spawn,          SHCMD("wallpaper -c") },

  /*Keybindings*/
        { MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_y,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_comma,  setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_period, setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_minus,  setlayout,      {.v = &layouts[1]} },
/*	{ MODKEY,                       XK_space,  setlayout,      {0} },*/
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
/*	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },*/
	{ MODKEY,                       XK_Tab,    shiftview,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Tab,    shiftview,      {.i = -1 } },
	{ MODKEY,                       XK_i,      setgaps,        {.i = -10 } },
	{ MODKEY,                       XK_p,      setgaps,        {.i = +10 } },
	{ MODKEY, 		        XK_o,      setgaps,        {.i = 0 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	{ MODKEY|ShiftMask,             XK_Escape, quit,           {0} },
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

