
#include<stdio.h> 			/* perror */
#include<stdlib.h>			/* exit	*/
#include<sys/types.h>		/* WNOHANG */
#include<sys/wait.h>		/* waitpid */
#include<string.h>			/* memset */

#include"driver.h"

struct hostapd_data
{
    int data;
};

extern struct wpa_driver_ops *wpa_drivers[];
/*
 * ģ��hostapd����driver
 * ע��call-down��driver call-up
 * call-down���ٰ���nl80211_global_init/nl80211_global_deinit,i802_init/i802_deinit
 * call-up���ٰ���wpa_supplicant_event,wpa_scan_results_free
 */
int main() 
{
    int i = 0;
	for (i = 0; wpa_drivers[i]; i++) 
	{
		if (wpa_drivers[i]->global_init) 
		{
			void * p = wpa_drivers[i]->global_init();
			if (p == NULL) {
				printf("global_init Failed to initialize\n");
				return -1;
			}
		}
		struct hostapd_data hapd;
		struct wpa_init_params params;
		if (wpa_drivers[i]->hapd_init) 
		{
			void * p = wpa_drivers[i]->hapd_init(&hapd,&params);
			if (p == NULL) {
				printf("hapd_init Failed to initialize\n");
				return -1;
			}		    
		}		    
	}
	printf("NL80211 initialized\n");
    return 0;
}

void wpa_supplicant_event(void *ctx, enum wpa_event_type event,
			  union wpa_event_data *data)
{
    return;
}

void wpa_scan_results_free(struct wpa_scan_results *res)
{
    return;   
}