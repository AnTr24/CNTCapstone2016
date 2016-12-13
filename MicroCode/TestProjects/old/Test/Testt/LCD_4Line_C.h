void lcdInit(void);

void lcdRWUp(void);
void lcdRWDown(void);

void lcdEUp(void);
void lcdEDown(void);

void lcdRSUp(void);
void lcdRSDown(void);

void lcdSDelay(void);
void lcdLDelay(void);

void lcdData(char);
void lcdBusy(void);
void lcdInst(char);

void lcdAddr(char);
void lcdCGAddr(char);
void lcdString(char*);
void lcdClear(void);

void Set_R_C(char,char);
void lcdLabels(char*,char*,char*,char*);