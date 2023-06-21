#include "stdio.h"
#include "epm/epm.h"
#include "tc/tc.h"
#include <sys/types.h>
#include <tcinit/tcinit.h>
#include <ps/ps.h>
#include <tccore/workspaceobject.h>
#include <sa/tcfile.h>
#include <string.h>
#include <fclasses/tc_string.h>
#include <fclasses/tc_date.h>
#include <tc/tc_util.h>
#include <nls/nls.h>
#include <iostream>
//#include <tie\tie.h>
#include <error_decode.h>
#include <stdio.h>
//#include <conio.h>
#include <stdlib.h>
#include <tc/tc.h>
#include <ae/ae.h>
#include <itk/mem.h>
#include <tc/emh.h>
#include <tccore/item.h>
#include <qry/qry.h>
#include <errno.h>
#include <ctype.h>
//#include <windows.h>
#include <sys/stat.h>
#include <unidefs.h>
#include <pom/pom/pom.h>
#include <tccore/aom.h>
#include <tccore/aom_prop.h>
#include <tc/tc_startup.h>
#include <epm/epm.h>
#include <ctime>

using namespace std;


extern int W4B_Register_CustomHandlers(METHOD_message_t* msg, va_list args);
extern int W4B_AssignEffectivityWithEndItem(EPM_action_message_t message);
int getcurrentdate(date_t* date,int days);
int getStatus(TC_argument_list_t *args, char** status);
int getActualStatusObject(std::string input, tag_t* releaseStatuses, int n_statuses ,tag_t** actualReleaseStatus);

