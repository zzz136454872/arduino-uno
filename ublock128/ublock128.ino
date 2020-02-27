/* @author f4prime
 * @email zzz136454872@163.com
 */
//使用半字节作为处理的单位
//加密和解密计算

#define speed

//#define right
#ifdef right
    #undef speed
#endif 

//获取低位和高位
#define high(a) (a>>4)
#define low(a) (a&0xf)

//根据长度显示指定位置内存
//for arduino version
//parameter:
//info: message for the print
//start: start address
//len: length 
void printmem(const void * const start, const int len, const char* info) 
{
    unsigned char *ptr = (unsigned char*)start;
    int i;
    Serial.print(info);
    for(i=0;i<len;i++)
    {
        if(i%16==0)
            Serial.write('\n');
        if(ptr[i] < 0xf)
            Serial.print(0);
        Serial.print(ptr[i],HEX);
        Serial.write(' ');
    }
    Serial.write('\n');
}



void ublock_128_128_keyschedule(const unsigned char* const key, unsigned char subkey[][32])
{
    unsigned char rc[16][16] = {{0x9,0x8,0x8,0xc,0xc,0x9,0xd,0xd},
                                {0xf,0x0,0xe,0x4,0xa,0x1,0xb,0x5},
                                {0x2,0x1,0x3,0x5,0x7,0x0,0x6,0x4},
                                {0x8,0x3,0x9,0x7,0xd,0x2,0xc,0x6},
                                {0xc,0x7,0xd,0x3,0x9,0x6,0x8,0x2},
                                {0x4,0xf,0x5,0xb,0x1,0xe,0x0,0xa},
                                {0x5,0xe,0x4,0xa,0x0,0xf,0x1,0xb},
                                {0x7,0xc,0x6,0x8,0x2,0xd,0x3,0x9},
                                {0x3,0x9,0x2,0xd,0x6,0x8,0x7,0xc},
                                {0xb,0x3,0xa,0x7,0xe,0x2,0xf,0x6},
                                {0xa,0x7,0xb,0x3,0xf,0x6,0xe,0x2},
                                {0x8,0xe,0x9,0xa,0xd,0xf,0xc,0xb},
                                {0xd,0xc,0xc,0x8,0x8,0xd,0x9,0x9},
                                {0x7,0x8,0x6,0xc,0x2,0x9,0x3,0xd},
                                {0x3,0x0,0x2,0x4,0x6,0x1,0x7,0x5},
                                {0xa,0x1,0xb,0x5,0xf,0x0,0xe,0x4}};
    unsigned char key_reg[32];
    unsigned char tmp01[16];
    unsigned char s_box[16]={0x7,0x4,0x9,0xc,0xb,0xa,0xd,0x8,0xf,0xe,0x1,0x6,0x0,0x3,0x2,0x5};
    unsigned char t_box[16]={0, 2, 4, 6, 8, 10, 12, 14, 3, 1, 7, 5, 11, 9, 15, 13};
    unsigned char pk[16]={6,0,8,13,1,15,5,10,4,9,12,2,11,3,7,14};
    int i,j;
    for(i=0;i<16;i++)
    {
        key_reg[2*i]=high(key[i]);
        key_reg[2*i+1]=low(key[i]);
    }
    memcpy(subkey[0],key_reg,32);
    for(i=0;i<16;i++)
    {
        for(j=0;j<16;j++)
            tmp01[j]=key_reg[pk[j]];
        for(j=0;j<8;j++)
        {
            key_reg[16+j]^=s_box[tmp01[j]^rc[i][j]];
            key_reg[24+j]^=t_box[tmp01[8+j]];
        }
        memcpy(key_reg,key_reg+16,16);
        memcpy(key_reg+16,tmp01+8,8);
        memcpy(key_reg+24,tmp01,8);
        memcpy(subkey[i+1],key_reg,32);
    }
}

void ublock_128_128_enc_block(const unsigned char *plain, unsigned char *const cipher, const unsigned char subkey[][32])
{
    int i,j;
    unsigned char reg[32];
    unsigned char reg_tmp[32];
    unsigned char s_box[16]={0x7,0x4,0x9,0xc,0xb,0xa,0xd,0x8,0xf,0xe,0x1,0x6,0x0,0x3,0x2,0x5};
    unsigned char pl_128_table[16]={2,3,6,7,8,9,12,13,0,1,4,5,14,15,10,11};
    //unsigned char pr_128_table[16]={0x4,0x5,0xe,0xf,0xa,0xb,0x0,0x1,0x2,0x3,0xc,0xd,0x8,0x9,0x6,0x7};
    unsigned char pr_128_table_a16[16]={0x14,0x15,0x1e,0x1f,0x1a,0x1b,0x10,0x11,0x12,0x13,0x1c,0x1d,0x18,0x19,0x16,0x17};
    //unsigned char lf1[16]={1,2,3,4,5,6,7,0,9,10,11,12,13,14,15,8};	
    unsigned char lf1_a16[16]={0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x10,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,0x18};	
    unsigned char lf2[16]={2,3,4,5,6,7,0,1,10,11,12,13,14,15,8,9};		
    unsigned char lf5[16]={5,6,7,0,1,2,3,4,13,14,15,8,9,10,11,12};		
    for(i=0;i<16;i++)
    {
        reg[2*i]=high(plain[i]);
        reg[2*i+1]=low(plain[i]);
    }

    for(i=0;i<16;i++)
    {
        for(j=0;j<32;j++)
            reg[j]=s_box[reg[j]^subkey[i][j]];

        for(j=0;j<16;j++)
            reg[j+16]^=reg[j];
        for(j=0;j<16;j++)
            reg[j]^=reg[lf1_a16[j]];
        for(j=0;j<16;j++)
            reg[16+j]^=reg[lf2[j]];
        for(j=0;j<16;j++)
            reg[j]^=reg[lf2[j]+16];
        for(j=0;j<16;j++)
            reg[j+16]^=reg[lf5[j]];
        for(j=0;j<16;j++)
            reg[j]^=reg[j+16];
        
        for(j=0;j<16;j++)
        {
            reg_tmp[j]=reg[pl_128_table[j]];
            reg_tmp[16+j]=reg[pr_128_table_a16[j]];
        }
        memcpy(reg,reg_tmp,32);
    }
    for(j=0;j<32;j++)
        reg[j]^=subkey[16][j];
    for(j=0;j<16;j++)
        cipher[j]=(reg[2*j]<<4)|reg[2*j+1];
}

//ublock 128 128
//解密一个分组的函数
//输入的subkey 是扩展之后的密钥
void ublock_128_128_dec_block(const unsigned char *cipher, unsigned char *const plain, const unsigned char subkey[][32])
{
    int i,j;
    unsigned char reg[32];
    unsigned char reg_tmp[32];
    unsigned char s_box_inv[16]={0xc,0xa,0xe,0xd,0x1,0xf,0xb,0x0,0x7,0x2,0x5,0x4,0x3,0x6,0x9,0x8};
    //unsigned char pr_128_inv_table[16]={6,7,8,9,0,1,14,15,12,13,4,5,10,11,2,3};
    unsigned char pr_128_inv_table_a16[16]={0x16,0x17,0x18,0x19,0x10,0x11,0x1e,0x1f,0x1c,0x1d,0x14,0x15,0x1a,0x1b,0x12,0x13};
    unsigned char pl_128_inv_table[16]={8,9,0,1,10,11,2,3,4,5,14,15,6,7,12,13};
    //unsigned char lf1[16]={1,2,3,4,5,6,7,0,9,10,11,12,13,14,15,8};	
    unsigned char lf1_a16[16]={0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x10,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,0x18};	
    unsigned char lf2[16]={2,3,4,5,6,7,0,1,10,11,12,13,14,15,8,9};		
    unsigned char lf5[16]={5,6,7,0,1,2,3,4,13,14,15,8,9,10,11,12};		
    for(i=0;i<16;i++)
    {
        reg[2*i]=high(cipher[i]);
        reg[2*i+1]=low(cipher[i]);
    }
    
    for(i=16;i>0;i--)
    {
        //printf("round: %d\n",i);
        for(j=0;j<32;j++)
            reg[j]=reg[j]^subkey[i][j];
        for(j=0;j<16;j++)
        {
            reg_tmp[j]=reg[pl_128_inv_table[j]];
            reg_tmp[16+j]=reg[pr_128_inv_table_a16[j]];
        }

        for(j=0;j<16;j++)
            reg[j]=reg_tmp[j]^reg_tmp[j+16];
        for(j=0;j<16;j++)
            reg[j+16]=reg[lf5[j]]^reg_tmp[j+16];
        for(j=0;j<16;j++)
            reg[j]^=reg[16+lf2[j]];
        for(j=0;j<16;j++)
            reg[j+16]^=reg[lf2[j]];
        for(j=0;j<16;j++)
            reg[j]^=reg[lf1_a16[j]];
        for(j=0;j<16;j++)
            reg[j+16]^=reg[j];

        for(j=0;j<32;j++)
            reg[j]=s_box_inv[reg[j]];
    }
    for(j=0;j<32;j++)
        reg[j]^=subkey[0][j];
    for(j=0;j<16;j++)
        plain[j]=(reg[2*j]<<4)|reg[2*j+1];
}

//使用ecb模式加密数据
//由于加密数据中可能出现0x00因此，使用 in_len 表示输入数据的长度
int ublock_128_128_enc_ecb(unsigned char *input, int in_len, unsigned char *output, int *out_len, unsigned char *key)
{
	int i;
    unsigned char subkey[17][32];
	ublock_128_128_keyschedule(key,subkey);
    //printmem(subkey,17*32,"subkey");
	for (i = 0; i < in_len / 16; i++)
	{
		ublock_128_128_enc_block(input+i*16, output+i*16, subkey);
	}
	*out_len = in_len - in_len % 16;
	return 0;
}

//ecb 模式解密函数
int ublock_128_128_dec_ecb(unsigned char *input, int in_len, unsigned char *output, int *out_len , unsigned char *key)
{
    int i;
    unsigned char subkey[17][32];
	ublock_128_128_keyschedule(key,subkey);
	for (i = 0; i < in_len / 16; i++)
	{
		ublock_128_128_dec_block(input+i*16, output+i*16, subkey);
	}
	*out_len = in_len - in_len % 16;
	return 0;
} 

#ifdef right
    int righttest()
    {
        unsigned char key[16]   = {0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10};
        unsigned char plain[16]   = {0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10};
        unsigned char cipher[16];
        unsigned char decrypt[16];
        int in_len=16,out_len=16;
        printmem(plain,16,"plain");
        ublock_128_128_enc_ecb(plain,in_len, cipher,&out_len,key);
        printmem(plain,16,"plain");
        printmem(cipher,16,"cipher");
        ublock_128_128_dec_ecb(cipher,in_len,decrypt,&out_len,key);
        printmem(decrypt,16,"decrypt");
        return 0;
    }
#endif
   
#ifdef speed
    int speedtest()
    {
        unsigned char key[16]   = {0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10};
        unsigned char plain[1024];
        unsigned char cipher[1024];
        int in_len=1024,out_len;
        int i;
        //数据初始化
        for(i=0;i<1024;i++)
            plain[i]=i%155;
        for(i=0;i<2;i++)
            ublock_128_128_enc_ecb(plain,in_len,cipher,&out_len,key);
        return 0;
    }

    long mstimer()
    {
        unsigned long  time_start;	//开始时间
        unsigned long time_over;	//结束时间
        time_start = millis();	//计时开始
        //这里添加需要测试的函数
        speedtest();
        time_over=millis();	//计时结束
        unsigned long time_used=time_over-time_start;
        Serial.print("run_time: ");
        Serial.print(time_used);
        Serial.println("ms");
        return time_used;
    }
#endif

void setup()
{
    Serial.begin(9600);
    Serial.println("start");
}
   
void loop()
{
    delay(3000);
    #ifdef right
        righttest();
    #endif 
    #ifdef speed
        mstimer();
    #endif 
    //Serial.print("\n\n\n\n");
    return 0;
}
