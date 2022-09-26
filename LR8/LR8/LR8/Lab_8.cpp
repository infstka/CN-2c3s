#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
using namespace std;


unsigned long CharToLong(const char* ip_)
{
	unsigned long out = 0;//число для IP-адреса
	char* buff;
	buff = new char[3];
	//буфер для хранения одного октета
	for (int i = 0, j = 0, k = 0; ip_[i] != '\0'; i++, j++)
	{
		if (ip_[i] != '.') //если не точка
			buff[j] = ip_[i]; // записать символ в буфер
		if (ip_[i] == '.' || ip_[i + 1] == '\0')
		{
			// если следующий октет или последний
			out <<= 8; //сдвинуть число на 8 бит
			if (atoi(buff) > 255)
				return NULL;
			// еcли октет больше 255 – ошибка
			out += (unsigned long)atoi(buff);
			//преобразовать и добавить 
			//к числу IP-адреса
			k++;
			j = -1;
			delete[]buff;
			buff = new char[3];
		}
	}
	return out;
}

bool CheckAddress(const char* ip_)
{
	int points = 0, // количество точек
		numbers = 0; // значение октета
	char* buff; // буфер для одного октета
	buff = new char[3];
	for (int i = 0; ip_[i] != '\0'; i++)
	{ // для строки IP-адреса
		if (ip_[i] <= '9' && ip_[i] >= '0') // если цифра
		{
			if (numbers > 3) return false;
			//если больше трех чисел в октете – ошибка
			buff[numbers++] = ip_[i];
			//скопировать в буфер
		}
		else
			if (ip_[i] == '.') // если точка
			{
				if (atoi(buff) > 255)
					// проверить диапазон октета
					return false;
				if (numbers == 0)
					//если числа нет - ошибка
					return false;
				numbers = 0;
				points++;
				delete[]buff;
				buff = new char[3];
			}
			else
			{
				return false;
				throw - 1;
			}
	}
	if (points != 3)
		// если количество точек в IP-адресе не 3 - ошибка
		return false;
	if (numbers == 0 || numbers > 3)
		return false;
	return true;
}

bool CheckMask(const char* mask_)
{
	int points = 0, // количество точек
		numbers = 0; // значение октета
	char* buff; // буфер для одного октета
	buff = new char[3];
	for (int i = 0; mask_[i] != '\0'; i++)
	{ // для строки IP-адреса
		if (mask_[i] <= '9' && mask_[i] >= '0') // если цифра
		{
			if (numbers > 3) return false;
			//если больше трех чисел в октете – ошибка
			buff[numbers++] = mask_[i];
			//скопировать в буфер
		}
		else
			if (mask_[i] == '.') // если точка
			{
				if (atoi(buff) > 255)
					// проверить диапазон октета
					return false;
				if (numbers == 0)
					//если числа нет - ошибка
					return false;
				numbers = 0;
				points++;
				delete[]buff;
				buff = new char[3];
			}
			else
			{
				return false;
				throw - 1;
			}
	}
	if (points != 3)
		// если количество точек в IP-адресе не 3 - ошибка
		return false;
	if (numbers == 0 || numbers > 3)
		return false;
	return true;
}



unsigned int* IpToArr(const char* ipChar)
{
	unsigned int* ipArr = new unsigned int[4]; // численное хранение массива 4 октетов
	char* buff;
	buff = new char[3]; //строковое хранение одного октета

	for (int i = 0, j = 0, k = 0; ipChar[i] != '\0'; i++, j++)
	{
		if (ipChar[i] != '.') //если не точка
			buff[j] = ipChar[i]; // записать символ в буфер
		if (atoi(buff) > 255)
		{
			cout << "Error(Число не входит в диапазон [0;255])";
			throw - 1;
		}
		if (ipChar[i] == '.' || ipChar[i + 1] == '\0')
		{
			ipArr[k] = atoi(buff);
			k++;
			j = -1;
			delete[] buff;
			buff = new char[3];
		}
	}
	return ipArr;
}

unsigned int* MaskToArr(const char* maskChar)
{
	unsigned int* maskArr = new unsigned int[4]; // массив 4 октетов
	char* buff;
	buff = new char[3]; // один октет

	for (int i = 0, j = 0, k = 0; maskChar[i] != '\0'; i++, j++)
	{
		if (maskChar[i] != '.') // если не точка
			buff[j] = maskChar[i]; // записать символ в буфер
		if (atoi(buff) > 255)
		{
			cout << "Error(Число не входит в диапазон [0;255])";
			throw - 1;
		}
		if (maskChar[i] == '.' || maskChar[i + 1] == '\0')
		{
			maskArr[k] = atoi(buff);
			k++;
			j = -1;
			delete[] buff;
			buff = new char[3];
		}
	}
	return maskArr;
}

unsigned int ToBinary(unsigned long dec)
{
	unsigned int bin = 0, j;
	for (j = 0; dec > 0; j++)
	{
		bin += (dec % 2) * pow(10.0, j);
		dec /= 2;
	}
	return bin;
}

char* IntToChar(unsigned int* binMask)
{
	char* charMask = new char[20];
	char* bufMask1 = new char[10];
	char* bufMask2 = new char[10];
	char* bufMask3 = new char[10];

	_itoa(binMask[0], charMask, 10);
	_itoa(binMask[1], bufMask1, 10);
	_itoa(binMask[2], bufMask2, 10);
	_itoa(binMask[3], bufMask3, 10);

	strcat(charMask, bufMask1);
	strcat(charMask, bufMask2);
	strcat(charMask, bufMask3);

	return charMask;
}

bool CountOfOne(char* charMask)
{
	bool flagEndOf1 = false;
	for (int i = 0; i < strlen(charMask); i++)
	{
		if (charMask[i] == '0')
			flagEndOf1 = true;
		if (flagEndOf1 && charMask[i] == '1')
		{
			return false;
			throw - 1;
		}
	}
	return true;
}

int main()
{
	setlocale(LC_ALL, "ru");
	const char* ip;
	const char* mask;
	string ip_, mask_;
	cout << "Введите IP: ";
	cin >> ip_;
	cout << "\nВведите Mask: ";
	cin >> mask_;
	cout << endl;


	ip = ip_.c_str();
	mask = mask_.c_str();

	unsigned int* intMask = MaskToArr(mask);
	unsigned int* binMask = new unsigned int[4];
	for (int i = 0; i < 4; i++)
	{
		binMask[i] = ToBinary(intMask[i]);
	}

	// Проверка IP и Mask на правильность
	if (CheckAddress(ip))
	{
		cout << "IP-адрес: " << ip << "\n";
	}
	else
	{
		cout << "Error(Неправильный IP-adress)" << "\n";
		throw - 1;
	}
	if (CheckMask(mask) && CountOfOne(IntToChar(binMask)))
	{
		cout << "Маска: " << mask << "\n";
	}
	else
	{
		cout << "Error(Неправильная маска)" << "\n";
		throw - 1;
	}

	// Получение subnet, host , broadcast
	unsigned int* intIp = IpToArr(ip);
	unsigned int* subnet = new unsigned int[4];
	for (int i = 0; i < 4; i++)
	{
		subnet[i] = intIp[i] & intMask[i];
	}
	cout << "\nNetwork ID: [" << subnet[0] << "." << subnet[1] << "." << subnet[2] << "." << subnet[3] << "]\n";

	unsigned int* host = new unsigned int[4];
	for (int i = 0; i < 4; i++)
	{
		host[i] = intIp[i] & ~intMask[i];
	}
	cout << "Host ID: [" << host[0] << "." << host[1] << "." << host[2] << "." << host[3] << "]\n";

	unsigned int* broadcast = new unsigned int[4];
	for (int i = 0; i < 4; i++)
	{
		if ((intIp[i] & intMask[i]) == 0)
		{
			broadcast[i] = 255;
		}
		else
		{
			broadcast[i] = (intIp[i] & intMask[i]);
		}
	}
	cout << "Broadcast адрес: [" << broadcast[0] << "." << broadcast[1] << "." << broadcast[2] << "." << broadcast[3] << "]\n";
}