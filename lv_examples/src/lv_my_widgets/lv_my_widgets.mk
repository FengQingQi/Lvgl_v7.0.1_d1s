CSRCS += lv_my_widgets.c
CSRCS += ac_off.c
CSRCS += ac_on.c
CSRCS += company.c
CSRCS += home.c
CSRCS += hour_img.c
CSRCS += light1_all.c
CSRCS += light1_off.c
CSRCS += light1_on.c
CSRCS += light2_all.c
CSRCS += light2_off.c
CSRCS += light2_on.c
CSRCS += light3_off.c
CSRCS += light3_on.c
CSRCS += minute_img.c
CSRCS += second_img.c
CSRCS += watch_bg.c

DEPPATH += --dep-path $(LVGL_DIR)/lv_examples/src/lv_my_widgets
VPATH += :$(LVGL_DIR)/lv_examples/src/lv_my_widgets
CFLAGS += "-I$(LVGL_DIR)/lv_examples/src/lv_my_widgets"

