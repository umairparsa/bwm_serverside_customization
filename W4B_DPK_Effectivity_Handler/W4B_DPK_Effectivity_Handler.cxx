#include "W4B_DPK_Effectivity_Handler.hxx"


int W4B_Register_CustomHandlers(METHOD_message_t* msg, va_list args){
	int ifail = ITK_ok;
	ifail = EPM_register_action_handler("W4B_AssignEffectivityWithEndItem", "Assigns Effectivity Date and EndItem", W4B_AssignEffectivityWithEndItem);

	return ifail;
}

int W4B_AssignEffectivityWithEndItem(EPM_action_message_t message){
	int ifail = ITK_ok;
	tag_t *attachments = NULL;
	tag_t rootTask = NULLTAG;
	int noAttachments = 0;
	ifail = EPM_ask_root_task(message.task, &rootTask);
	ifail = EPM_ask_attachments(rootTask, EPM_target_attachment, &noAttachments, &attachments);
	//get ReleaseStatus object
	tag_t targetObj = attachments[0];
	int prop_count = 0;
	char** prop_names = NULL;
	tag_t* releaseStatus;
	int n_statuses;
	
	ifail = AOM_ask_value_tags(targetObj, "release_status_list", &n_statuses, &releaseStatus);

	int n_dates = 1;

	date_t dat = NULLDATE;
	getcurrentdate(&dat, 0);

	date_t* start_end_values = NULL;
	start_end_values = (date_t*)malloc(sizeof(date_t) * 2);

	start_end_values[0] = dat;

	tag_t* ref_attachments = NULL;
	int ref_noAttachemnts = 0 ;
	//get reference attachemnt 
	ifail = EPM_ask_attachments(rootTask, EPM_reference_attachment, &ref_noAttachemnts, &ref_attachments);
	//get reference object (PRISMA TOP)	
	tag_t end_item = ref_attachments[0];
	tag_t effectivity_object;

	ifail =  WSOM_effectivity_create(releaseStatus[0], end_item, &effectivity_object);
	AOM_save(releaseStatus[0]);

	ifail = WSOM_eff_set_dates(releaseStatus[0], effectivity_object, n_dates, start_end_values, EFFECTIVITY_open_ended, false);
	AOM_save(releaseStatus[0]);
	char* msg = NULL;
	EMH_ask_error_text(ifail,& msg);
	TC_write_syslog("\nifail = %s", msg);
	
	return ifail;
}



int getcurrentdate(date_t* date,int days){
	time_t rawtime;

	struct tm* timeinfo;

	char buffer[80];
	
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	date->year = timeinfo->tm_year + 1900;
	date->month = timeinfo->tm_mon;
	date->day = timeinfo->tm_mday+ days;
	date->hour = timeinfo->tm_hour;
	date->minute = timeinfo->tm_min;
	date->second = timeinfo->tm_sec;

	return 0;
}
