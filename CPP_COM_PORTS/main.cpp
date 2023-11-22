#include <windows.h>
#include <iostream>
using namespace std;


/*


API 

ReadCOM - ������ �������, �����, ������ ��������� ������...
WriteFile - ��������� ������� �� ��� ����

*/

HANDLE hSerial;


void ReadCOM()
{
    DWORD iSize;
    char sReceivedChar;
    while (true)
    {
        ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0);  // �������� 1 ����
        if (iSize > 0)   // ���� ���-�� �������, �������
            cout << sReceivedChar;
    }
}

int main()
{

	LPCTSTR sPortName = L"COM6";
	hSerial = ::CreateFile(sPortName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (hSerial == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
        {
            cout << "serial port does not exist.\n";
        }
        cout << "some other error occurred.\n";
    }

    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams))
    {
        cout << "getting state error\n";
    }
    dcbSerialParams.BaudRate = CBR_115200;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams))
    {
        cout << "error setting serial port state\n";
    }

    char data[] = "123456789";  // ������ ��� ��������
    DWORD dwSize = sizeof(data);   // ������ ���� ������
    DWORD dwBytesWritten;    // ��� ����� ���������� ���������� ���������� ����

   BOOL iRet = WriteFile(hSerial, data, dwSize, &dwBytesWritten, NULL);

    cout << dwSize << " Bytes in string. " << dwBytesWritten << " Bytes sended. " << endl;


    while (1)
    {
       // ReadCOM();
        WriteFile(hSerial, data, dwSize, &dwBytesWritten, NULL);
           cout << dwSize << " Bytes in string. " << dwBytesWritten << " Bytes sended. " << endl;

        Sleep(1000);
        cout << data << "\n";
    }
    return 0;
}
