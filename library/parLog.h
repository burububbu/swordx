typedef struct parLog{
	char* name;
	int cw;
	int iw;
	double time;
	struct parLog *next;
}parLog;

parLog* createLogNode(char*, int, int, parLog*);
