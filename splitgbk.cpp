
#include <iostream>

int split_gbk_str(const unsigned char* str, int len, int split_num)
{
    int char_flag = 0;//0-ASCII 1-双字节首字节，2-双字节尾字节,-1非法字符

    for (int i = 0; i < len ; i++)
    {
        if (str[i] == 0x0 && i <split_num)
        {
             return -1;//意外的结束符
        }
      
        if (char_flag == 1)
        {
            if ((str[i - 1] >= 0xa1 && str[i - 1] <= 0xa9)
                || (str[i - 1] >= 0xb0 && str[i - 1] <= 0xf7))
            {
                if (str[i] <= 0xfe && str[i] >= 0xa1)//GBK1
                {
                    char_flag = 2;
                }
                else
                {
                    char_flag = -1;
                }

                if (str[i - 1] >= 0xa8 && str[i - 1] <= 0xa9)
                {
                    if (str[i] <= 0xa0 && str[i] >= 0x40 && str[i] != 0x7f)//GBK5
                    {
                        char_flag = 2;
                    }
                    else
                    {
                        char_flag = -1;
                    }
                }
            }

            else if ((str[i - 1] >= 0x81 && str[i - 1] <= 0xa0))
            {
                if ((str[i] <= 0xfe && str[i] >= 0x40) && (str[i] != 0x7f))//GBK3
                {
                    char_flag = 2;
                }
                else
                {
                    char_flag = -1;
                }
            }
            else if ((str[i - 1] >= 0xaa && str[i - 1] <= 0xfe))
            {
                if ((str[i] <= 0xA0 && str[i] >= 0x40) && (str[i] != 0x7f))//GBK4
                {
                    char_flag = 2;
                }
                else
                {
                    char_flag = -1;
                }
            }
            else if ((str[i - 1] >= 0xaa && str[i - 1] <= 0xaf)
                || (str[i - 1] >= 0xf8 && str[i - 1] <= 0xfe))
            {
                if (str[i] <= 0xfe && str[i] >= 0xa1)//用户定义
                {
                    char_flag = 2;
                }
                else
                {
                    char_flag = -1;
                }
            }
            else if (str[i - 1] >= 0xa1 && str[i - 1] <= 0xa7)
            {
                if ((str[i] <= 0xa0 && str[i] >= 0x40) && (str[i] != 0x7f))//用户定义
                {
                    char_flag = 2;
                }
                else
                {
                    char_flag = -1;
                }
            }
        }
        else
        {
            if (str[i] < 0x81)
            {
                char_flag = 0;
            }
            else if ((str[i] >= 0x81) && (str[i] <= 0xfe))
            {
                char_flag = 1;
            }
        }

        if (i == split_num)
        {
            if (char_flag == 1)
            {
                return 1;//表示当前分割点为首字节后
            }
            else if ((char_flag == 1) || (char_flag == 2))
            {
                return 2;//表示当前分割点为完整字符后
            }
            else
            {
                return 3;//当前分割点有非法字符
            }
        }
    }
}


int main()
{
   /* HMODULE module = LoadLibrary("thread.dll");
    if (module == NULL)
    {
        cout << "error" << endl;
    }*/


    int i = 1;

    unsigned char a[4] = { 0x48,0xa1,0xae,0x0 };
    std::cout << split_gbk_str(a, 4, 3)<<endl;
    std::cout << "Hello World!\n";



}
