// generated by Fast Light User Interface Designer (fluid) version 1.0011

#include "radio.h"

int main(int argc, char **argv) {
  Fl_Window* w;
  { Fl_Window* o = new Fl_Window(462, 453);
    w = o;
    new Fl_Button(20, 10, 160, 30, "Fl_Button");
    new Fl_Return_Button(20, 50, 160, 30, "Fl_Return_Button");
    new Fl_Light_Button(20, 90, 160, 30, "Fl_Light_Button");
    { Fl_Check_Button* o = new Fl_Check_Button(20, 130, 160, 30, "Fl_Check_Button");
      o->box(FL_UP_BOX);
      o->down_box(FL_DIAMOND_DOWN_BOX);
    }
    { Fl_Round_Button* o = new Fl_Round_Button(20, 170, 160, 30, "Fl_Round_Button");
      o->box(FL_UP_BOX);
      o->down_box(FL_ROUND_DOWN_BOX);
    }
    { Fl_Group* o = new Fl_Group(190, 10, 70, 120);
      o->box(FL_THIN_UP_FRAME);
      { Fl_Check_Button* o = new Fl_Check_Button(190, 10, 70, 30, "radio");
        o->type(102);
        o->down_box(FL_DIAMOND_DOWN_BOX);
      }
      { Fl_Check_Button* o = new Fl_Check_Button(190, 40, 70, 30, "radio");
        o->type(102);
        o->down_box(FL_DIAMOND_DOWN_BOX);
      }
      { Fl_Check_Button* o = new Fl_Check_Button(190, 70, 70, 30, "radio");
        o->type(102);
        o->down_box(FL_DIAMOND_DOWN_BOX);
      }
      { Fl_Check_Button* o = new Fl_Check_Button(190, 100, 70, 30, "radio");
        o->type(102);
        o->down_box(FL_DIAMOND_DOWN_BOX);
      }
      o->end();
    }
    { Fl_Group* o = new Fl_Group(270, 10, 90, 115);
      o->box(FL_THIN_UP_BOX);
      { Fl_Button* o = new Fl_Button(280, 20, 20, 20, "radio");
        o->type(102);
        o->selection_color(1);
        o->align(FL_ALIGN_RIGHT);
      }
      { Fl_Button* o = new Fl_Button(280, 45, 20, 20, "radio");
        o->type(102);
        o->selection_color(1);
        o->align(FL_ALIGN_RIGHT);
      }
      { Fl_Button* o = new Fl_Button(280, 70, 20, 20, "radio");
        o->type(102);
        o->selection_color(1);
        o->align(FL_ALIGN_RIGHT);
      }
      { Fl_Button* o = new Fl_Button(280, 95, 20, 20, "radio");
        o->type(102);
        o->selection_color(1);
        o->align(FL_ALIGN_RIGHT);
      }
      o->end();
    }
    o->end();
  }
  w->show(argc, argv);
  return Fl::run();
}