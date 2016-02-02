// generated by Fast Light User Interface Designer (fluid) version 1.0011

#include "valuators.h"

static void callback(Fl_Widget* o, void*) {
  printf("%g     \r", ((Fl_Valuator*)o)->value());
fflush(stdout);
}

int main(int argc, char **argv) {
  Fl_Window* w;
  { Fl_Window* o = new Fl_Window(567, 506, "Valuator classes, showing values for type()");
    w = o;
    o->color(43);
    o->selection_color(43);
    { Fl_Box* o = new Fl_Box(10, 10, 280, 210, "Fl_Slider");
      o->box(FL_ENGRAVED_BOX);
      o->labelfont(1);
      o->align(FL_ALIGN_TOP|FL_ALIGN_INSIDE);
    }
    { Fl_Slider* o = new Fl_Slider(30, 45, 20, 145, "0");
      o->selection_color(1);
      o->labelsize(8);
      o->callback((Fl_Callback*)callback);
      o->align(FL_ALIGN_TOP);
    }
    { Fl_Slider* o = new Fl_Slider(70, 55, 20, 145, "FL_VERT_FILL_SLIDER");
      o->type(2);
      o->selection_color(1);
      o->labelsize(8);
      o->callback((Fl_Callback*)callback);
    }
    { Fl_Slider* o = new Fl_Slider(105, 45, 20, 145, "FL_VERT_NICE_SLIDER");
      o->type(4);
      o->box(FL_FLAT_BOX);
      o->color(10);
      o->selection_color(1);
      o->labelsize(8);
      o->callback((Fl_Callback*)callback);
      o->align(FL_ALIGN_TOP);
    }
    { Fl_Box* o = new Fl_Box(10, 230, 280, 205, "Fl_Value_Slider");
      o->box(FL_ENGRAVED_BOX);
      o->labelfont(1);
      o->align(FL_ALIGN_TOP|FL_ALIGN_INSIDE);
    }
    { Fl_Value_Slider* o = new Fl_Value_Slider(30, 260, 30, 145, "0");
      o->selection_color(1);
      o->labelsize(8);
      o->callback((Fl_Callback*)callback);
      o->align(FL_ALIGN_TOP);
    }
    { Fl_Value_Slider* o = new Fl_Value_Slider(70, 275, 30, 140, "FL_VERT_FILL_SLIDER");
      o->type(2);
      o->selection_color(1);
      o->labelsize(8);
      o->callback((Fl_Callback*)callback);
    }
    { Fl_Value_Slider* o = new Fl_Value_Slider(110, 260, 20, 145, "FL_VERT_NICE_SLIDER");
      o->type(4);
      o->box(FL_FLAT_BOX);
      o->color(10);
      o->selection_color(1);
      o->labelsize(8);
      o->callback((Fl_Callback*)callback);
      o->align(FL_ALIGN_TOP);
    }
    { Fl_Slider* o = new Fl_Slider(140, 80, 130, 20, "FL_HORIZONTAL");
      o->type(1);
      o->selection_color(1);
      o->labelsize(8);
      o->callback((Fl_Callback*)callback);
    }
    { Fl_Slider* o = new Fl_Slider(140, 120, 130, 20, "FL_HOR_FILL_SLIDER");
      o->type(3);
      o->selection_color(1);
      o->labelsize(8);
      o->callback((Fl_Callback*)callback);
    }
    { Fl_Slider* o = new Fl_Slider(140, 160, 130, 20, "FL_HOR_NICE_SLIDER");
      o->type(5);
      o->box(FL_FLAT_BOX);
      o->color(10);
      o->selection_color(1);
      o->labelsize(8);
      o->callback((Fl_Callback*)callback);
    }
    { Fl_Value_Slider* o = new Fl_Value_Slider(140, 290, 130, 20, "FL_HOR_SLIDER");
      o->type(1);
      o->selection_color(1);
      o->labelsize(8);
      o->callback((Fl_Callback*)callback);
    }
    { Fl_Value_Slider* o = new Fl_Value_Slider(140, 330, 130, 20, "FL_HOR_FILL_SLIDER");
      o->type(3);
      o->selection_color(1);
      o->labelsize(8);
      o->callback((Fl_Callback*)callback);
    }
    { Fl_Box* o = new Fl_Box(430, 10, 125, 120, "Fl_Adjuster");
      o->box(FL_ENGRAVED_BOX);
      o->labelfont(1);
      o->align(FL_ALIGN_TOP|FL_ALIGN_INSIDE);
    }
    { Fl_Value_Slider* o = new Fl_Value_Slider(140, 370, 130, 20, "FL_HOR_NICE_SLIDER");
      o->type(5);
      o->box(FL_FLAT_BOX);
      o->color(10);
      o->selection_color(1);
      o->labelsize(8);
      o->callback((Fl_Callback*)callback);
    }
    { Fl_Adjuster* o = new Fl_Adjuster(440, 60, 75, 25, "w()>h()");
      o->labelsize(8);
      o->callback((Fl_Callback*)callback);
    }
    { Fl_Adjuster* o = new Fl_Adjuster(520, 35, 25, 75, "w()<h()");
      o->labelsize(8);
      o->callback((Fl_Callback*)callback);
    }
    { Fl_Box* o = new Fl_Box(345, 135, 210, 115, "Fl_Counter");
      o->box(FL_ENGRAVED_BOX);
      o->labelfont(1);
      o->align(FL_ALIGN_TOP|FL_ALIGN_INSIDE);
    }
    { Fl_Counter* o = new Fl_Counter(360, 160, 180, 30, "0");
      o->labelsize(8);
      o->callback((Fl_Callback*)callback);
    }
    { Fl_Counter* o = new Fl_Counter(360, 205, 180, 30, "FL_SIMPLE_COUNTER");
      o->type(1);
      o->labelsize(8);
      o->callback((Fl_Callback*)callback);
    }
    { Fl_Box* o = new Fl_Box(300, 260, 255, 105, "Fl_Dial");
      o->box(FL_ENGRAVED_BOX);
      o->labelfont(1);
      o->align(FL_ALIGN_TOP|FL_ALIGN_INSIDE);
    }
    { Fl_Dial* o = new Fl_Dial(315, 280, 65, 65, "0");
      o->color(10);
      o->selection_color(1);
      o->labelsize(8);
      o->value(0.5);
      o->callback((Fl_Callback*)callback);
      o->angles(0,315);
    }
    { Fl_Dial* o = new Fl_Dial(395, 280, 65, 65, "FL_LINE_DIAL");
      o->type(1);
      o->color(10);
      o->selection_color(1);
      o->labelsize(8);
      o->value(0.5);
      o->callback((Fl_Callback*)callback);
    }
    { Fl_Dial* o = new Fl_Dial(475, 280, 65, 65, "FL_FILL_DIAL");
      o->type(2);
      o->color(10);
      o->selection_color(1);
      o->labelsize(8);
      o->value(1);
      o->callback((Fl_Callback*)callback);
      o->angles(0,360);
    }
    { Fl_Box* o = new Fl_Box(300, 375, 145, 120, "Fl_Roller");
      o->box(FL_ENGRAVED_BOX);
      o->labelfont(1);
      o->align(FL_ALIGN_TOP|FL_ALIGN_INSIDE);
    }
    { Fl_Roller* o = new Fl_Roller(315, 390, 20, 95, "0");
      o->labelsize(8);
      o->callback((Fl_Callback*)callback);
    }
    { Fl_Roller* o = new Fl_Roller(340, 430, 90, 20, "FL_HORIZONTAL");
      o->type(1);
      o->labelsize(8);
      o->callback((Fl_Callback*)callback);
    }
    { Fl_Box* o = new Fl_Box(10, 445, 140, 50, "Fl_Value_Input");
      o->box(FL_ENGRAVED_BOX);
      o->labelfont(1);
      o->align(FL_ALIGN_TOP|FL_ALIGN_INSIDE);
    }
    { Fl_Box* o = new Fl_Box(455, 375, 100, 120, "Some widgets have color(FL_GREEN) and color2(FL_RED) to show the areas these \
effect.");
      o->box(FL_BORDER_FRAME);
      o->color(0);
      o->selection_color(0);
      o->labelsize(10);
      o->align(FL_ALIGN_WRAP);
    }
    { Fl_Box* o = new Fl_Box(155, 445, 135, 50, "Fl_Value_Output");
      o->box(FL_ENGRAVED_BOX);
      o->labelfont(1);
      o->align(FL_ALIGN_TOP|FL_ALIGN_INSIDE);
    }
    { Fl_Value_Input* o = new Fl_Value_Input(30, 460, 110, 30, "0");
      o->labelsize(8);
      o->maximum(100);
      o->step(0.1);
      o->callback((Fl_Callback*)callback);
    }
    { Fl_Value_Output* o = new Fl_Value_Output(170, 460, 110, 30, "0");
      o->labelsize(8);
      o->maximum(100);
      o->step(0.1);
      o->callback((Fl_Callback*)callback);
    }
    { Fl_Box* o = new Fl_Box(295, 10, 130, 120, "   Fl_Scrollbar");
      o->box(FL_ENGRAVED_BOX);
      o->labelfont(1);
      o->align(FL_ALIGN_TOP_LEFT|FL_ALIGN_INSIDE);
    }
    { Fl_Scrollbar* o = new Fl_Scrollbar(395, 20, 20, 105, "0");
      o->labelsize(8);
      o->maximum(100);
      o->callback((Fl_Callback*)callback);
      o->align(FL_ALIGN_TOP);
    }
    { Fl_Scrollbar* o = new Fl_Scrollbar(300, 65, 95, 20, "FL_HORIZONTAL");
      o->type(1);
      o->labelsize(8);
      o->maximum(100);
      o->callback((Fl_Callback*)callback);
    }
    o->end();
  }
  w->show(argc, argv);
  return Fl::run();
}