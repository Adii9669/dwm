#define TAGKEYS(KEY, TAG)                                                                                              \
  { MODKEY, KEY, view, { .ui = 1 << TAG } }, { MODKEY | ControlMask, KEY, toggleview, { .ui = 1 << TAG } },            \
      { MODKEY | ShiftMask, KEY, tag, { .ui = 1 << TAG } },                                                            \
      { MODKEY | ControlMask | ShiftMask, KEY, toggletag, { .ui = 1 << TAG } },


#include "fibonacci.c"
#include <stddef.h>
#include "selfrestart.c"
/* Color schemes */
#define SchemeNorm 0
#define SchemeSel 1

#include "/home/milo/suckless/dwm/themes/mytheme.h"

/* Appearance */
static const unsigned int borderpx    = 2;
static const unsigned int gappx       = 2;
static const unsigned int snap        = 55;
static const int          showbar     = 1;
static const int          topbar      = 1;
static const char*        fonts[]     = { "JetBrainsMono Nerd Font:size=15" };
static const char         dmenufont[] = "LiberationMono Bold:size=15";

/* Color settings */
static const char* colors[][3] = {
  { col_gray3, col_gray2, col_gray2 },
  { col_gray4, col_cyan, col_cyan },
};

/* Tags */
static const char* tags[] = { "  ", "  ", " 󰓓", "  ", "  " };

/* Rules */
static const Rule rules[] = {
  { "Brave-browser", NULL, NULL, 0, 0, -1 },
  { "kitty", NULL, NULL, 0, 0, -1 },
  { "Spotify", NULL, NULL, 1 << 4, 0, -1 },
  { "Thunar", NULL, NULL, 1 << 4, 0, -1 },
};

/* Layouts */
static const float mfact          = 0.55;
static const int   nmaster        = 1;
static const int   resizehints    = 1;
static const int   lockfullscreen = 1;

static const int showsystray             = 1;
static const int systraypinning          = 0;
static const int systraypinningfailfirst = 1;
static const int systrayspacing          = 2;
static const int systrayonleft           = 0;

static const Layout layouts[] = {
  { "[]=", tile },
  { "><>", NULL },
  { "[M]", monocle },
  { "[D]", deck },
  { "[@]", spiral },
  { "[\\]", dwindle },
};


/* Key Definitions */
#define SHCMD(cmd)                                                                                                     \
  {                                                                                                                    \
    .v = (const char*[]) {                                                                                             \
      "/bin/sh", "-c", cmd, NULL                                                                                       \
    }                                                                                                                  \
  }

/* Commands */
static char        dmenumon[2] = "0";
static const char* dmenucmd[]  = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", NULL };
static const char* termcmd[]   = { "kitty", NULL };
static const char* brave[]     = { "brave", NULL };
static const char* firefox[]   = { "firefox", NULL };
static const char* thunarcmd[] = { "Thunar" };

#define MODKEY Mod4Mask // Super/Win key
static const Key keys[] = {
  /* modifier            key        function        argument */
  { MODKEY, XK_r, togglebar, { 0 } },


  // restart doesn't work after recomplie
  { MODKEY | ShiftMask, XK_r, self_restart, { 0 } },
  

  //travel and quit
  { MODKEY, XK_j, focusstack, { .i = +1 } },
  { MODKEY, XK_k, focusstack, { .i = -1 } },
  { MODKEY, XK_i, incnmaster, { .i = +1 } },
  { MODKEY, XK_d, incnmaster, { .i = -1 } },
  { MODKEY, XK_Tab, view, { 0 } },
  { MODKEY, XK_q, killclient, { 0 } },



  // layouts
  { MODKEY, XK_t, setlayout, { .v = &layouts[0] } },
  { MODKEY, XK_c, setlayout, { .v = &layouts[3] } },
  { MODKEY | ShiftMask, XK_f, setlayout, { .v = &layouts[1] } },
  { MODKEY, XK_m, setlayout, { .v = &layouts[2] } },
  { MODKEY, XK_Return, setlayout, { 0 } },
  { MODKEY | ShiftMask, XK_Return, togglefloating, { 0 } },
  { MODKEY, XK_y, setlayout, { .v = &layouts[3] } },
  { MODKEY | ShiftMask, XK_y, setlayout, { .v = &layouts[4] } },
  { MODKEY, XK_space, zoom, { 0 } },


  // view at one or last page
  { MODKEY, XK_0, view, { .ui = ~0 } },
  { MODKEY | ShiftMask, XK_0, tag, { .ui = ~0 } },


  // focus need to find about this
  { MODKEY, XK_comma, focusmon, { .i = -1 } },
  { MODKEY, XK_period, focusmon, { .i = +1 } },
  { MODKEY | ShiftMask, XK_comma, tagmon, { .i = -1 } },
  { MODKEY | ShiftMask, XK_period, tagmon, { .i = +1 } },
  // gaps
  { MODKEY, XK_minus, setgaps, { .i = -1 } },
  { MODKEY, XK_equal, setgaps, { .i = +1 } },
  { MODKEY | ShiftMask, XK_equal, setgaps, { .i = 0 } },
  // applications
  { MODKEY, XK_p, spawn, { .v = dmenucmd } },
  { MODKEY, XK_w, spawn, { .v = termcmd } },
  { MODKEY, XK_b, spawn, { .v = brave } },
  { MODKEY, XK_f, spawn, { .v = firefox } },
  { MODKEY, XK_i, cycletags, { .i = -1 } },
  { MODKEY, XK_o, cycletags, { .i = +1 } },


  //resize
  { MODKEY, XK_h, setmfact, { .f = -0.05 } },
  { MODKEY, XK_l, setmfact, { .f = +0.05 } },

  //thunar and rule
  { MODKEY, XK_e, spawn, { .v = thunarcmd } },
  { MODKEY, XK_e, view, { .ui = 1 << 4 } },

  /* Tag keys */
  // TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2)
  // TAGKEYS(XK_4, 3) TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5)
  // TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7) TAGKEYS(XK_9, 8)

  TAGKEYS(XK_1, 8) TAGKEYS(XK_2, 7) TAGKEYS(XK_3, 6) TAGKEYS(XK_4, 5) TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 3) TAGKEYS(XK_7, 2)
      TAGKEYS(XK_8, 1) TAGKEYS(XK_9, 0)



          { MODKEY | ShiftMask, XK_q, quit, { 0 } },
};



#define Button8 8
#define Button9 9

/* Buttons */
static const Button buttons[] = {
  { ClkLtSymbol, 0, Button1, setlayout, { 0 } },
  { ClkLtSymbol, 0, Button3, setlayout, { .v = &layouts[2] } },
  { ClkWinTitle, 0, Button2, zoom, { 0 } },
  { ClkStatusText, 0, Button2, spawn, { .v = termcmd } },
  { ClkClientWin, MODKEY, Button1, movemouse, { 0 } },
  { ClkClientWin, MODKEY, Button2, togglefloating, { 0 } },
  { ClkClientWin, MODKEY, Button3, resizemouse, { 0 } },
  { ClkTagBar, 0, Button1, view, { 0 } },
  { ClkTagBar, 0, Button3, toggleview, { 0 } },
  { ClkTagBar, MODKEY, Button1, tag, { 0 } },
  { ClkTagBar, MODKEY, Button3, toggletag, { 0 } },
  { ClkTagBar, 0, Button5, cycletags, { .i = -1 } },
  { ClkTagBar, 0, Button4, cycletags, { .i = +1 } },
  { ClkWinTitle, 0, Button5, cycletags, { .i = -1 } },
  { ClkWinTitle, 0, Button4, cycletags, { .i = +1 } },
};

/* Autostart applications */
static const char* const autostart[] = {
  "picom",
  "-b",
  "--animations",
  NULL,
};
