#include "lv_my_widgets.h"
#include "../../lv_examples.h"

#include   <stdio.h>
#include   <time.h>

static void night_dark_set(int mode);
static void lv_smarthome_boot_animation(int time);
static void lv_demo_tabview(void);
static void tabview1_create(lv_obj_t * parent);
static void tabview2_create(lv_obj_t * parent);
static void tabview3_create(lv_obj_t * parent);
static void watch_time(lv_obj_t * parent);
static void get_sys_time(lv_obj_t * parent);


LV_IMG_DECLARE(light1_on); //����ͼƬ
LV_IMG_DECLARE(light1_off); //����ͼƬ
LV_IMG_DECLARE(light2_on); //����ͼƬ
LV_IMG_DECLARE(light2_off); //����ͼƬ
LV_IMG_DECLARE(light3_on); //����ͼƬ
LV_IMG_DECLARE(light3_off); //����ͼƬ
LV_IMG_DECLARE(light1_all); //����ͼƬ
LV_IMG_DECLARE(light2_all); //����ͼƬ
LV_IMG_DECLARE(ac_on); //����ͼƬ
LV_IMG_DECLARE(ac_off); //����ͼƬ
LV_IMG_DECLARE(home); //����ͼƬ
LV_IMG_DECLARE(company); //����ͼƬ


LV_IMG_DECLARE(watch_bg);
LV_IMG_DECLARE(hour_img);
LV_IMG_DECLARE(minute_img);
LV_IMG_DECLARE(second_img);


static lv_obj_t * background_animation;
static lv_obj_t * tabview;
static lv_obj_t * tabview1;
static lv_obj_t * tabview2;
static lv_obj_t * tabview3;
static lv_obj_t * btn_img1;//�ƹ�1
static lv_obj_t * btn_img2;//�ƹ�2
static lv_obj_t * btn_img3;//�ƹ�3
static lv_obj_t * btn_img4;//���еƹ�

static lv_obj_t * second_bg;//
static lv_obj_t * minute_bg;//
static lv_obj_t * hour_bg;//

static bool led_status = false;//LED��־λ
static bool led_status1 = false;//LED1��־λ
static bool led_status2 = false;//LED1��־λ
static bool led_status3 = false;//LED1��־λ



int Year, Month, Date, Hour, Minute, Second;

/**
 * ҹ��ģʽ or �ռ�ģʽ
 * @param mode 0 ҹ��ģʽ 1 �ռ�ģʽ
 */
static void night_dark_set(int mode)
{
    uint32_t flag = LV_THEME_MATERIAL_FLAG_LIGHT;
    if(mode==0) flag = LV_THEME_MATERIAL_FLAG_DARK;
        LV_THEME_DEFAULT_INIT(lv_theme_get_color_primary(), lv_theme_get_color_secondary(),
                flag,
                lv_theme_get_font_small(), lv_theme_get_font_normal(), lv_theme_get_font_subtitle(), lv_theme_get_font_title());
}

//��������(�ƹ�1)�ص�
static void btn_event_led1(lv_obj_t * obj, lv_event_t event)
{
	if (event == LV_EVENT_PRESSED)
	{
		//���󱻰���ʱ����,ÿ�ΰ���ʱֻ����һ��
        if (led_status1 == false)
        {
		    printf("\nled1 on\n");
            led_status1 = true;
        }
        else
        {
		    printf("\nled1 off\n");
            led_status1 = false;
        }
	}
}
//��������(�ƹ�2)�ص�
static void btn_event_led2(lv_obj_t * obj, lv_event_t event)
{
	if (event == LV_EVENT_PRESSED)
	{
		//���󱻰���ʱ����,ÿ�ΰ���ʱֻ����һ��
        if (led_status2 == false)
        {
		    printf("\nled2 on\n");
            led_status2 = true;
        }
        else
        {
		    printf("\nled2 off\n");
            led_status2 = false;
        }
	}
}
//��������(�ƹ�1)�ص�
static void btn_event_led3(lv_obj_t * obj, lv_event_t event)
{
	if (event == LV_EVENT_PRESSED)
	{
		//���󱻰���ʱ����,ÿ�ΰ���ʱֻ����һ��
        if (led_status3 == false)
        {
		    printf("\nled3 on\n");
            led_status3 = true;
        }
        else
        {
		    printf("\nled3 off\n");
            led_status3 = false;
        }
	}
}

//���������ص�
LV_EVENT_CB_DECLARE(event_handler)
{
    // switch (e)
    // {
    //     case LV_EVENT_CLICKED://���
    //         break;
    //     case LV_EVENT_RELEASED://��ѹ
    //         break;
    //     case LV_EVENT_PRESSED://�ɿ�
    //         break;
    //     case LV_EVENT_LONG_PRESSED://����
    //         break;
    //     default:break;
    // }
}

//��������(���еƹ�)�ص�
static void btn_event_all_led(lv_obj_t * obj, lv_event_t event)
{
	if (event == LV_EVENT_PRESSED)
	{
		//���󱻰���ʱ����,ÿ�ΰ���ʱֻ����һ��
        if (led_status == false)
        {
            //ͼƬ��ť �ƹ�1
            lv_imgbtn_set_checkable(btn_img1, true);                    //ʹ�ܰ���ͼƬ��ת
            lv_imgbtn_toggle(btn_img1);                                 //���÷�ת
	        lv_obj_align(btn_img1, NULL, LV_ALIGN_IN_TOP_LEFT, 50, 50); //���ϽǶ���

            //ͼƬ��ť �ƹ�2
            lv_imgbtn_set_checkable(btn_img2, true);                    //ʹ�ܰ���ͼƬ��ת
            lv_imgbtn_toggle(btn_img2);                                 //���÷�ת
	        lv_obj_align(btn_img2, NULL, LV_ALIGN_IN_TOP_LEFT, 180, 50);//���ϽǶ���

            //ͼƬ��ť �ƹ�3
            lv_imgbtn_set_checkable(btn_img3, true);                    //ʹ�ܰ���ͼƬ��ת
            lv_imgbtn_toggle(btn_img3);                                 //���÷�ת
	        lv_obj_align(btn_img3, NULL, LV_ALIGN_IN_TOP_LEFT, 310, 50);//���ϽǶ���

		    printf("\nled on\n");
            led_status = true;
        }
        else
        {
            //ͼƬ��ť �ƹ�1
            lv_imgbtn_set_checkable(btn_img1, true);                    //ʹ�ܰ���ͼƬ��ת
            lv_imgbtn_toggle(btn_img1);                                 //���÷�ת
            lv_obj_align(btn_img1, NULL, LV_ALIGN_IN_TOP_LEFT, 50, 50); //���ϽǶ���

            //ͼƬ��ť �ƹ�2
            lv_imgbtn_set_checkable(btn_img2, true);                    //ʹ�ܰ���ͼƬ��ת
            lv_imgbtn_toggle(btn_img2);                                 //���÷�ת
            lv_obj_align(btn_img2, NULL, LV_ALIGN_IN_TOP_LEFT, 180, 50);//���ϽǶ���

            //ͼƬ��ť �ƹ�3
            lv_imgbtn_set_checkable(btn_img3, true);                    //ʹ�ܰ���ͼƬ��ת
            lv_imgbtn_toggle(btn_img3);                                 //���÷�ת
            lv_obj_align(btn_img3, NULL, LV_ALIGN_IN_TOP_LEFT, 310, 50);//���ϽǶ���

		    printf("\nled off\n");
            led_status = false;
        }
	}
}

void lv_my_widget(int boot_time)
{/*
    uint32_t flag = LV_THEME_MATERIAL_FLAG_DARK;

    LV_THEME_DEFAULT_INIT(lv_theme_get_color_primary(),
                          lv_theme_get_color_secondary(),
                          flag,
                          lv_theme_get_font_small(),
                          lv_theme_get_font_normal(),
                          lv_theme_get_font_subtitle(),
                          lv_theme_get_font_title());
*/
    /* �������� */
    lv_smarthome_boot_animation(boot_time);

    /* tabview */
    lv_demo_tabview();

    // ����tabview��Ļ,����Ч��ΪLV_SCR_LOAD_ANIM_FADE_ON,�л�ʱ��Ϊ500ms,�ӳ� boot_time ��ӵ�һ����ʼ�л����л���ɺ�ɾ������������Ļ
    //lv_scr_load_anim(tabview, LV_SCR_LOAD_ANIM_FADE_ON, 500, boot_time*100+100, true);
}

/**
 * ��������
 * @param time ����ʱ������λ���룩.
 */
static void lv_smarthome_boot_animation(int time)
{
    //����
    background_animation = lv_obj_create(lv_scr_act(), NULL);       //���������������Ϊ NULL ������һ����Ļ
	lv_obj_clean_style_list(background_animation, LV_OBJ_PART_MAIN);//��ն�����
	lv_obj_set_style_local_bg_opa(background_animation, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_100);//������ɫ���Ƕ�100%����ֵԽ�ͣ���ɫԽ͸��
	lv_obj_set_style_local_bg_color(background_animation, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);//���ñ�����ɫΪ��ɫ
    lv_obj_set_size(background_animation, LV_HOR_RES, LV_VER_RES);  //���ø������

    //������
    lv_obj_t* bar = lv_bar_create(lv_scr_act(), NULL);              //��������������
    lv_obj_set_size(bar, 200, 15);                                  //�������ڽ�����ĳ���
    lv_obj_align(bar, NULL, LV_ALIGN_CENTER, 0, 0);                 //�������ڽ��������ʾ
    lv_bar_set_range(bar, 1, 100);                                  //��������Χ
    lv_bar_set_anim_time(bar, time*100);                            //����lv_bar�������Ķ���ʱ��
    lv_bar_set_value(bar, 100, LV_ANIM_ON);                         //��������ֵ, LV_ANIM_ON ��������
    lv_obj_set_style_local_bg_color(bar, LV_BAR_PART_BG, LV_STATE_DEFAULT, LV_COLOR_WHITE);     //���ñ���Ϊ��ɫ
    lv_obj_set_style_local_bg_color(bar, LV_BAR_PART_INDIC, LV_STATE_DEFAULT, LV_COLOR_ORANGE); //����ǰ��Ϊ��ɫ

    //�ı�
    lv_obj_t * label = lv_label_create(lv_scr_act(), NULL);         //������ǩ����
    lv_label_set_recolor(label, true);                              //������ǩ����
    lv_label_set_text(label, "#FFA500 Software is upgrading #");    //�����ı�����
    lv_obj_align(label, bar, LV_ALIGN_CENTER, 0, -30);              //���ı����ս���������
}

/**
 * ��ǩ��
 */
static void lv_demo_tabview(void)
{
    tabview = lv_tabview_create(lv_scr_act(), NULL);                        //����һ��tabview����δ���ص���ʾ
    lv_tabview_set_btns_pos(tabview, LV_TABVIEW_TAB_POS_NONE);      //����tabview
    night_dark_set(0);                                              //ҹ��ģʽ

    tabview1 = lv_tabview_add_tab(tabview, "HOME");
    tabview2 = lv_tabview_add_tab(tabview, "LED");
    tabview3 = lv_tabview_add_tab(tabview, "MUSIC");

    tabview1_create(tabview1);
    tabview2_create(tabview2);
    tabview3_create(tabview3);

}

/**
 * ��ǩҳ1: ����Ԥ����ʱ��
 */
static void tabview1_create(lv_obj_t * parent)
{
    lv_obj_t * label = lv_label_create(tabview1, NULL);             //������ǩ����
    lv_label_set_recolor(label, true);                              //�ı�������ɫ
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);               //��ǩ�ڽ��������ʾ
    lv_label_set_text(label, "page1");                              //�����ı�����

    watch_time(parent);
}

/**
 * ��ǩҳ2: �ƹ����
 */
static void tabview2_create(lv_obj_t * parent)
{
    //ͼƬ��ť �ƹ�1
	btn_img1 = lv_imgbtn_create(parent, NULL);                      //����ͼƬ����
	lv_imgbtn_set_src(btn_img1, LV_BTN_STATE_PRESSED, &light1_off); //����״̬ͼƬ
	lv_imgbtn_set_src(btn_img1, LV_BTN_STATE_RELEASED, &light1_on); //̧��״̬ͼƬ
    lv_imgbtn_set_src(btn_img1, LV_BTN_STATE_CHECKED_RELEASED, &light1_off);//��⵽���ɿ�״̬ͼƬ
    lv_imgbtn_set_src(btn_img1, LV_BTN_STATE_CHECKED_PRESSED, &light1_on);  //��⵽����״̬ͼƬ
    lv_imgbtn_set_checkable(btn_img1, true);                        //ʹ�ܰ���ͼƬ��ת
    lv_imgbtn_toggle(btn_img1);                                     //���÷�ת
	lv_obj_align(btn_img1, NULL, LV_ALIGN_IN_TOP_LEFT, 50, 50);     //���ϽǶ���
    lv_obj_set_event_cb(btn_img1, btn_event_led1);                  //���ð�ť�ص�

    //ͼƬ��ť �ƹ�2
	btn_img2 = lv_imgbtn_create(parent, NULL);                      //����ͼƬ����
	lv_imgbtn_set_src(btn_img2, LV_BTN_STATE_PRESSED, &light2_off); //����״̬ͼƬ
	lv_imgbtn_set_src(btn_img2, LV_BTN_STATE_RELEASED, &light2_on); //̧��״̬ͼƬ
    lv_imgbtn_set_src(btn_img2, LV_BTN_STATE_CHECKED_RELEASED, &light2_off);//��⵽���ɿ�״̬ͼƬ
    lv_imgbtn_set_src(btn_img2, LV_BTN_STATE_CHECKED_PRESSED, &light2_on);  //��⵽����״̬ͼƬ
    lv_imgbtn_set_checkable(btn_img2, true);                        //ʹ�ܰ���ͼƬ��ת
    lv_imgbtn_toggle(btn_img2);                                     //���÷�ת
	lv_obj_align(btn_img2, NULL, LV_ALIGN_IN_TOP_LEFT, 180, 50);    //���ϽǶ���
    lv_obj_set_event_cb(btn_img2, btn_event_led2);                  //���ð�ť�ص�

    //ͼƬ��ť �ƹ�3

	btn_img3 = lv_imgbtn_create(parent, NULL);                      //����ͼƬ����
	lv_imgbtn_set_src(btn_img3, LV_BTN_STATE_PRESSED, &light3_off); //����״̬ͼƬ
	lv_imgbtn_set_src(btn_img3, LV_BTN_STATE_RELEASED, &light3_on); //̧��״̬ͼƬ
    lv_imgbtn_set_src(btn_img3, LV_BTN_STATE_CHECKED_RELEASED, &light3_off);//��⵽���ɿ�״̬ͼƬ
    lv_imgbtn_set_src(btn_img3, LV_BTN_STATE_CHECKED_PRESSED, &light3_on);  //��⵽����״̬ͼƬ
    lv_imgbtn_set_checkable(btn_img3, true);                        //ʹ�ܰ���ͼƬ��ת
    lv_imgbtn_toggle(btn_img3);                                     //���÷�ת
	lv_obj_align(btn_img3, NULL, LV_ALIGN_IN_TOP_LEFT, 310, 50);    //���ϽǶ���
    lv_obj_set_event_cb(btn_img3, btn_event_led3);                  //���ð�ť�ص�

    //ͼƬ��ť �ƹ�ȫ��
	btn_img4 = lv_imgbtn_create(parent, NULL);                      //����ͼƬ����
	lv_imgbtn_set_src(btn_img4, LV_BTN_STATE_PRESSED, &light2_all); //����״̬ͼƬ
	lv_imgbtn_set_src(btn_img4, LV_BTN_STATE_RELEASED, &light1_all);//̧��״̬ͼƬ
    lv_imgbtn_set_src(btn_img4, LV_BTN_STATE_CHECKED_RELEASED, &light2_all);//��⵽���ɿ�״̬ͼƬ
    lv_imgbtn_set_src(btn_img4, LV_BTN_STATE_CHECKED_PRESSED, &light1_all); //��⵽����״̬ͼƬ
    lv_imgbtn_set_checkable(btn_img4, true);                        //ʹ�ܰ���ͼƬ��ת
    lv_imgbtn_toggle(btn_img4);                                     //���÷�ת
	lv_obj_align(btn_img4, NULL, LV_ALIGN_IN_TOP_LEFT, 50, 180);    //���ϽǶ���
    lv_obj_set_event_cb(btn_img4, btn_event_all_led);               //���ð�ť�ص�

    //ͼƬ��ť �յ�
	lv_obj_t* btn_img5 = lv_imgbtn_create(parent, NULL);            //����ͼƬ����
	lv_imgbtn_set_src(btn_img5, LV_BTN_STATE_PRESSED, &ac_off);     //����״̬ͼƬ
	lv_imgbtn_set_src(btn_img5, LV_BTN_STATE_RELEASED, &ac_on);     //̧��״̬ͼƬ
    lv_imgbtn_set_src(btn_img5, LV_BTN_STATE_CHECKED_RELEASED, &ac_off);    //��⵽���ɿ�״̬ͼƬ
    lv_imgbtn_set_src(btn_img5, LV_BTN_STATE_CHECKED_PRESSED, &ac_on);      //��⵽����״̬ͼƬ
    lv_imgbtn_set_checkable(btn_img5, true);                        //ʹ�ܰ���ͼƬ��ת
    lv_imgbtn_toggle(btn_img5);                                     //���÷�ת
	lv_obj_align(btn_img5, NULL, LV_ALIGN_IN_TOP_LEFT, 245, 180);   //���ϽǶ���
    lv_obj_set_event_cb(btn_img5, event_handler);                   //���ð�ť�ص�

    //ͼƬ��ť �ؼ�ģʽ
	lv_obj_t* btn_img6 = lv_imgbtn_create(parent, NULL);            //����ͼƬ����
	lv_imgbtn_set_src(btn_img6, LV_BTN_STATE_PRESSED, &home);       //����״̬ͼƬ
	lv_imgbtn_set_src(btn_img6, LV_BTN_STATE_RELEASED, &home);      //̧��״̬ͼƬ
    lv_imgbtn_set_src(btn_img6, LV_BTN_STATE_CHECKED_RELEASED, &home);      //��⵽���ɿ�״̬ͼƬ
    lv_imgbtn_set_src(btn_img6, LV_BTN_STATE_CHECKED_PRESSED, &home);       //��⵽����״̬ͼƬ
    lv_imgbtn_set_checkable(btn_img6, true);                        //ʹ�ܰ���ͼƬ��ת
    lv_imgbtn_toggle(btn_img6);                                     //���÷�ת
	lv_obj_align(btn_img6, NULL, LV_ALIGN_IN_TOP_LEFT, 50, 310);    //���ϽǶ���
    lv_obj_set_event_cb(btn_img6, event_handler);                   //���ð�ť�ص�

    //ͼƬ��ť ���ģʽ
	lv_obj_t* btn_img7 = lv_imgbtn_create(parent, NULL);            //����ͼƬ����
	lv_imgbtn_set_src(btn_img7, LV_BTN_STATE_PRESSED, &company);    //����״̬ͼƬ
	lv_imgbtn_set_src(btn_img7, LV_BTN_STATE_RELEASED, &company);   //̧��״̬ͼƬ
    lv_imgbtn_set_src(btn_img7, LV_BTN_STATE_CHECKED_RELEASED, &company);   //��⵽���ɿ�״̬ͼƬ
    lv_imgbtn_set_src(btn_img7, LV_BTN_STATE_CHECKED_PRESSED, &company);    //��⵽����״̬ͼƬ
    lv_imgbtn_set_checkable(btn_img7, true);                        //ʹ�ܰ���ͼƬ��ת
    lv_imgbtn_toggle(btn_img7);                                     //���÷�ת
	lv_obj_align(btn_img7, NULL, LV_ALIGN_IN_TOP_LEFT, 245, 310);   //���ϽǶ���
    lv_obj_set_event_cb(btn_img7, event_handler);                   //���ð�ť�ص�

}

/**
 * ��ǩҳ3: ���ֲ�����
 */
static void tabview3_create(lv_obj_t * parent)
{
    //�ı�
    lv_obj_t * label = lv_label_create(parent, NULL);               //������ǩ����
    lv_label_set_recolor(label, true);                              //�ı�������ɫ
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);               //��ǩ�ڽ��������ʾ
    lv_label_set_text(label, "page3");                              //�����ı�����
}

//ʱ��
static void watch_time(lv_obj_t * parent)
{
    //����
    lv_obj_t * background_img = lv_img_create(parent, NULL);        //���������������Ϊ NULL ������һ����Ļ
	lv_obj_clean_style_list(background_img, LV_OBJ_PART_MAIN);      //��ն�����
	lv_img_set_src(background_img, &watch_bg);                      //���ر���
    lv_obj_set_size(background_img, 430, 430);                      //���ø������
    // lv_obj_set_auto_realign(background_img, true);
    lv_obj_align(background_img, parent, LV_ALIGN_CENTER, 0, 0);    //��ǩ�ڽ��������ʾ

    //ʱ��
    hour_bg = lv_img_create(parent, NULL);                          //���������������Ϊ NULL ������һ����Ļ
	lv_obj_clean_style_list(hour_bg, LV_OBJ_PART_MAIN);             //��ն�����
	lv_img_set_src(hour_bg, &hour_img);                             //����ʱ��
    lv_obj_set_size(hour_bg, 430, 430);                             //���ø������
    lv_obj_align(hour_bg, background_img, LV_ALIGN_CENTER, 0, 0);   //��ǩ�ڽ��������ʾ
    lv_img_set_angle(hour_bg, Hour);                                //ʱ����ת

    //����
    minute_bg = lv_img_create(parent, NULL);                        //���������������Ϊ NULL ������һ����Ļ
	lv_obj_clean_style_list(minute_bg, LV_OBJ_PART_MAIN);           //��ն�����
	lv_img_set_src(minute_bg, &minute_img);                         //���ط���
    lv_obj_set_size(minute_bg, 430, 430);                           //���ø������
    lv_obj_align(minute_bg, background_img, LV_ALIGN_CENTER, 0, 0); //��ǩ�ڽ��������ʾ
    lv_img_set_angle(minute_bg, Minute*60);                         //������ת

    //����
    second_bg = lv_img_create(parent, NULL);                        //���������������Ϊ NULL ������һ����Ļ
	lv_obj_clean_style_list(second_bg, LV_OBJ_PART_MAIN);           //��ն�����
	lv_img_set_src(second_bg, &second_img);                         //��������
    lv_obj_set_size(second_bg, 430, 430);                           //���ø������
    lv_obj_align(second_bg, background_img, LV_ALIGN_CENTER, 0, 0); //��ǩ�ڽ��������ʾ
    lv_img_set_angle(second_bg, Second*60);                         //������ת

    lv_task_create((lv_task_cb_t)get_sys_time, 1000, LV_TASK_PRIO_LOW, NULL);     //1������
}

//��ȡϵͳʱ��
static void get_sys_time(lv_obj_t * parent)
{
    struct tm * time_out;
    long ts;

    ts = time(NULL);
    time_out = localtime(&ts);

    Year = time_out-> tm_year+1900;//��
    Month = time_out-> tm_mon+1;   //��
    Date = time_out-> tm_mday;     //��
    Hour = time_out-> tm_hour;     //ʱ
    Minute = time_out-> tm_min;    //��
    Second = time_out-> tm_sec;    //��
    //printf("\n%d-%d-%d %d:%d:%d\n", Year, Month, Date, Hour, Minute, Second);

    //watch time
    lv_img_set_angle(hour_bg, Hour*60*5);                           //ʱ����ת
    lv_img_set_angle(minute_bg, Minute*60);                         //������ת
    lv_img_set_angle(second_bg, Second*60);                         //������ת
}

