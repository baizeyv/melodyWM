/* See LICENSE file for copyright and license details. */

#define SESSION_FILE "/tmp/dwm-session"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 10;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int horizpadbar        = 5;        /* horizontal padding for statusbar */
static const int vertpadbar         = 15;        /* vertical padding for statusbar */
static const double activeopacity   = 0.8f;     /* Window opacity when it's focused (0 <= opacity <= 1) */
static const double inactiveopacity = 0.6f;   /* Window opacity when it's inactive (0 <= opacity <= 1) */
static       Bool bUseOpacity       = True;     /* Starts with opacity on any unfocused windows */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const unsigned int baralpha = 0xa0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

static const char commandchar[] = "COMMAND";
static const char insertchar[] = "INSERT";

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ {0,0,0,0},                     {KEY,0,0,0},      view,           {.ui = 1 << TAG} }, \
	{ {ControlMask,0,0,0},           {KEY,0,0,0},      toggleview,     {.ui = 1 << TAG} }, \
	{ {ShiftMask,0,0,0},             {KEY,0,0,0},      tag,            {.ui = 1 << TAG} }, \
	{ {ControlMask|ShiftMask,0,0,0}, {KEY,0,0,0},      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static Key cmdkeys[] = {
	/* modifier                    keys                     function         argument */
	{ 0,                           XK_Escape,               clearcmd,        {0} },
	{ ControlMask,                 XK_g,                    clearcmd,        {0} },
	{ 0,                           XK_k,                    setkeymode,      {.ui = ModeInsert} },
};

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_Escape, setkeymode,     {.ui = ModeCommand} },
};

static Command commands[] = {
	/* modifier (4 keys)         keysyms (4 keys)         function        argument */
	{ {0,           0, 0, 0},    { XK_p,      0, 0, 0},   spawn,          {.v = dmenucmd } },
	{ {ShiftMask,   0, 0, 0},    { XK_Return, 0, 0, 0},   spawn,          {.v = termcmd } },
	{ {0,           0, 0, 0},    { XK_b,      0, 0, 0},   togglebar,      {0} },
	{ {0,           0, 0, 0},    { XK_y,      0, 0, 0},   toggleopacity,      {0} },
	{ {0,           0, 0, 0},    { XK_j,      0, 0, 0},   focusstack,     {.i = +1 } },
	{ {0,           0, 0, 0},    { XK_k,      0, 0, 0},   focusstack,     {.i = -1 } },
	{ {0,           0, 0, 0},    { XK_i,      0, 0, 0},   incnmaster,     {.i = +1 } },
	{ {0,           0, 0, 0},    { XK_d,      0, 0, 0},   incnmaster,     {.i = -1 } },
	{ {0,           0, 0, 0},    { XK_h,      0, 0, 0},   setmfact,       {.f = -0.05} },
	{ {0,           0, 0, 0},    { XK_l,      0, 0, 0},   setmfact,       {.f = +0.05} },
	{ {0,           0, 0, 0},    { XK_Return, 0, 0, 0},   zoom,           {0} },
	{ {ControlMask, 0, 0, 0},    { XK_i,      0, 0, 0},   view,           {0} },
	{ {0,   0, 0, 0},    { XK_c,      XK_c, 0, 0},   killclient,     {0} },
	{ {0,   0, 0, 0},    { XK_c,      XK_x, 0, 0},   killunsel,     {0} },
	{ {0,           0, 0, 0},    { XK_t,      0, 0, 0},   setlayout,      {.v = &layouts[0]} },
	{ {0,           0, 0, 0},    { XK_f,      0, 0, 0},   setlayout,      {.v = &layouts[1]} },
	{ {0,           0, 0, 0},    { XK_m,      0, 0, 0},   setlayout,      {.v = &layouts[2]} },
	{ {0,           0, 0, 0},    { XK_space,  0, 0, 0},   setlayout,      {0} },
	{ {ShiftMask,   0, 0, 0},    { XK_space,  0, 0, 0},   togglefloating, {0} },
	{ {0,           0, 0, 0},    { XK_0,      0, 0, 0},   view,           {.ui = ~0 } },
	{ {ShiftMask,   0, 0, 0},    { XK_0,      0, 0, 0},   tag,            {.ui = ~0 } },
	{ {0,           0, 0, 0},    { XK_comma,  0, 0, 0},   focusmon,       {.i = -1 } },
	{ {0,           0, 0, 0},    { XK_period, 0, 0, 0},   focusmon,       {.i = +1 } },
	{ {ShiftMask,   0, 0, 0},    { XK_comma,  0, 0, 0},   tagmon,         {.i = -1 } },
	{ {ShiftMask,   0, 0, 0},    { XK_period, 0, 0, 0},   tagmon,         {.i = +1 } },
	TAGKEYS(XK_1, 0)
	TAGKEYS(XK_2, 1)
	TAGKEYS(XK_3, 2)
	TAGKEYS(XK_4, 3)
	TAGKEYS(XK_5, 4)
	TAGKEYS(XK_6, 5)
	TAGKEYS(XK_7, 6)
	TAGKEYS(XK_8, 7)
	TAGKEYS(XK_9, 8)
	{ {0,   0, 0, 0},    { XK_q,      XK_q, 0, 0},   quit,           {0} },
	{ {0,   0, 0, 0},    { XK_q,      XK_r, 0, 0},   quit,           {1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
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
