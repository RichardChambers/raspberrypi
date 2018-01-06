
//clear screen
void lcd1602Clear(void);
void lcd1602Write (int xCol, int yRow, const char data[]);
void lcd1602Writef (int xCol, int yRow, const char *format, ... );
int lcd1602Open(int lcdAddr);
int lcd1602Close(void);

