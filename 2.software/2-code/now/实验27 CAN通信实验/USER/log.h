# include <stdio.h>

#define LOG 0
#define MSG_SD 0
#define MSG_CAN 0


#if LOG
		#define success(user,...)						printf("[success]\t%s\t%s\t"user"\r\n",__FILE__,__FUNCTION__,##__VA_ARGS__)
		#define info(file,format,...) 			printf("[info]\t"#file":  " format"\r\n",##__VA_ARGS__)
		#define error(errormsg,...)					//printf("[error]\t%s\t%s\t"errormsg"\r\n",__FILE__,__FUNCTION__,##__VA_ARGS__)
#else 
	#define success(user,...)		
	#define info(file,format,...)
	#define error(errormsg,...)	
#endif

#if MSG_SD
	#define info(file,format,...) 			printf("[info]"#file":  " format"\r\n",##__VA_ARGS__)
	#define success(file,process,...)		printf("[success]"#file":  "#process"" "\r\n",##__VA_ARGS__)
	#define error(file,process,...)			printf("[error]"#file":  "#process"" "\r\n",##__VA_ARGS__)
#else

#endif
	
#if MSG_CAN
	#define info(file,format,...) 			printf("[info]"#file":  " format"\r\n",##__VA_ARGS__)
	#define success(file,process,...)		printf("[success]"#file":  "#process"" "\r\n",##__VA_ARGS__)
	#define error(file,process,...)			printf("[error]"#file":  "#process"" "\r\n",##__VA_ARGS__)
#else

#endif


