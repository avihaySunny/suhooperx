/********************************************************************************************************************************************************/
/*                                                          WS3.h                                                                                        */
/*                                                      Avihay Asraf                                                                                    */                
/*                                                        April 2019                                                                                    */
/********************************************************************************************************************************************************/

char *StrToLow(char *str);                         /* returns a lowercase string, not a dup                               */
void BufferPrint(char **envp);                     /* prints envp buffer using indx from BufferAppend                     */
char **BufferAppend(char *envp[]);                /*  inner func appends the env_vars to big string and returns index     */
void BufferFree(char **index);                    /*  Frees a buffer and index if there's malloc fail                     */ 
void LastMan(unsigned int group_size);            /*  Finds out who is the last man stading, uses defined SIZE            */
char *strdup(const char *s); 
