// Сделано не мной //
#include <iostream>
#include <string>

using namespace std;

bool IsHex(string str)
{
	if (str.length() != 8) return 0;
	else
		for (int i = 0; i < str.length(); i++)
		{
			if (isdigit(str[i]) || (str[i] >= 'A' && str[i] <= 'F')) continue;
			else return 0;
		}
	return 1;
}

void HexToBin(string hex, string &bin )
{
	bin.clear();
	for (int i = 0; i < hex.length(); i++)
	{
		switch (hex[i])
		{
		case '0': bin += "0000"; break;
		case '1': bin += "0001"; break;
		case '2': bin += "0010"; break;
		case '3': bin += "0011"; break;
		case '4': bin += "0100"; break;
		case '5': bin += "0101"; break;
		case '6': bin += "0110"; break;
		case '7': bin += "0111"; break;
		case '8': bin += "1000"; break;
		case '9': bin += "1001"; break;
		case 'A': bin += "1010"; break;
		case 'B': bin += "1011"; break;
		case 'C': bin += "1100"; break;
		case 'D': bin += "1101"; break;
		case 'E': bin += "1110"; break;
		case 'F': bin += "1111"; break;
		}
	}

}

int binToDec(string str)
{
	int bin=0,mnozet=1;
	for (int i = str.length() - 1; i >= 0; i--)
	{
		if (str[i] == '1') bin += mnozet;
		mnozet *= 2;
	}
	return bin;
}

void Mantisa(string binStr, string &M)
{
	M += binStr.substr(9, binStr.length() - 9);
	for (int i = M.length()-1;; i--)
	{
		if (M[i] == '0') M.erase(i, 1);
		else break;
	}
}

void DecToBin(string &bin, int dec)
{
	int Dec = dec;
	string str;
	while (Dec != 0)
	{
		if (Dec % 2 == 0) str += '0';
		else str += '1';
		Dec = Dec / 2;
	}
	for (int i = (str.length()) - 1; i >= 0; i--)
	{
		bin += str[i];
	}
	if (!dec) bin += "0";
}

string OK(string digitalBin)
{
	string dBin = digitalBin;
	for (int i = 2; i < dBin.length(); i++)
	{
		if (dBin[i] == '0') dBin[i] = '1';
		else dBin[i] = '0';
	}
	return dBin;
}

string DK(string digitalBin)
{
	string dBin = digitalBin;
	for (int i = (dBin.length()) - 1;; i--)
	{
		if (dBin[i] == '0')
		{
			dBin[i] = '1';
			break;
		}
		else dBin[i] = '0';
	}
	return dBin;
}

void sumBin(string Astr, string Bstr, string &sum)
{
	int f = 0;
	sum.clear();
	for (int i = 0; i < Astr.length(); i++)
	{
		if (i != 2) sum += "0";
		else sum += ".";
	}
	for (int i = Astr.length() - 1; i >= 0; i--)
	{
		if (Astr[i] == '0' && Bstr[i] == '0' && f == 0) { sum[i] = '0'; continue; }
		if (Astr[i] == '0' && Bstr[i] == '0' && f == 1) { sum[i] = '1'; f = 0; continue; }
		if (Astr[i] == '0' && Bstr[i] == '1' && f == 0) { sum[i] = '1'; continue; }
		if (Astr[i] == '0' && Bstr[i] == '1' && f == 1) { sum[i] = '0'; f = 1; continue; }
		if (Astr[i] == '1' && Bstr[i] == '0' && f == 0) { sum[i] = '1'; continue; }
		if (Astr[i] == '1' && Bstr[i] == '0' && f == 1) { sum[i] = '0'; f = 1; continue; }
		if (Astr[i] == '1' && Bstr[i] == '1' && f == 0) { sum[i] = '0'; f = 1; continue; }
		if (Astr[i] == '1' && Bstr[i] == '1' && f == 1) { sum[i] = '1'; f = 1; continue; }
	}
}
  
void toLeft(string &str)
{
	str[0] = str[1];
	str[1] = str[3];
	for (int i = 3; i < str.length()-1; i++)
	{
		str[i] = str[i + 1];
	}
	str[str.length() - 1] = '0';
}

string BinToHex(string bin)
{
	string hex,four;
	for (int i = 0; i < 8; i++)
	{
		four = bin.substr(i * 4, 4);
		if (four == "0000") hex += '0';
		if (four == "0001") hex += '1';
		if (four == "0010") hex += '2';
		if (four == "0011") hex += '3';
		if (four == "0100") hex += '4';
		if (four == "0101") hex += '5';
		if (four == "0110") hex += '6';
		if (four == "0111") hex += '7';
		if (four == "1000") hex += '8';
		if (four == "1001") hex += '9';
		if (four == "1010") hex += 'A';
		if (four == "1011") hex += 'B';
		if (four == "1100") hex += 'C';
		if (four == "1101") hex += 'D';
		if (four == "1110") hex += 'E';
		if (four == "1111") hex += 'F';
	}
	return hex;
}

int main()
{
	setlocale(LC_ALL, "ru");

	int step = 1;
	string hexStrA, hexStrB, binStrA, binStrB;
	string SPA2, MA;
	int SPA10, IPA;
	string SPB2, MB;
	int SPB10, IPB;
	string mOper;
	int ZR;
	string IPA2, IPB2;
	string IPRsum;
	int IPR10;
	string curB, cur_B ;
	string tableRes1,tableRes2;
	string MR;
	string R2, spr2;
	string sym;
	while (step)
	{
		switch (step)
		{
			case 1:
			{
			cout << "Введите два вещественных шестнадцатеричных числа:\nA= ";
			getline(cin, hexStrA);
			cout << "B= ";
			getline(cin, hexStrB);
			step = 2;
			break;
			}
			case 2:
				if (IsHex(hexStrA) && IsHex(hexStrB)) step = 3;
				else { cout << "Ошибка ввода исходных чисел"<<endl<<endl; step = 1; }
				break;
			case 3:
				HexToBin(hexStrA, binStrA);
				HexToBin(hexStrB, binStrB);
				cout <<"\nA(2) = " << binStrA << endl;
				cout << "ZA = " << binStrA[0]<<endl;
				SPA2 = binStrA.substr(1,8);
				cout << "СПА(2) = " << SPA2<<endl;
				SPA10 = binToDec(SPA2);
				cout << "СПА(10) = " << SPA10<<endl;
				IPA = SPA10 - 127;
				cout << "ИПА(10) = " << IPA << endl;
				MA.clear();
				MA += "0,";
				Mantisa(binStrA, MA);
				if (hexStrA=="00000000") {cout << "mA = 0" << endl << endl;} else
				cout << "mA = " << MA << endl << endl;

				cout << "\nB(2) = " << binStrB << endl;
				cout << "ZB = " << binStrB[0] << endl;
				SPB2 = binStrB.substr(1, 8);
				cout << "СПB(2) = " << SPB2 << endl;
				SPB10 = binToDec(SPB2);
				cout << "СПB(10) = " << SPB10 << endl;
				IPB = SPB10 - 127;
				cout << "ИПB(10) = " << IPB << endl;
				MB.clear();
				MB += "0,";
				Mantisa(binStrB, MB);
				if (hexStrB == "00000000") { cout << "mB = 0" << endl << endl; }
				else
				cout << "mB = " << MB << endl << endl;
				step = 4;
				break;
			case 4:
				cout << "Введите номер выполняемой операции m:" << endl << "1 A+B" << endl << "2 A-B" << endl << "3 A*B" << endl << "4 A/B" << endl << "m= ";
				getline(cin, mOper);
				cout << endl;
				if (mOper.length() != 1 || !isdigit(mOper[0])) { cout << "Ошибка ввода номера выполняемой операции"<<endl; step = 4; break; }
				if (stoi(mOper)>4 || stoi(mOper)<1) { cout << "Ошибка ввода номера выполняемой операции"<<endl; step = 4; break; }
				if (stoi(mOper) == 1 || stoi(mOper) == 2 || stoi(mOper) == 3) { cout << "Операция не реализована"<<endl; step = 4; break;}
				if (stoi(mOper) == 4) step = 5;
				break;
			case 5:
				cout << "A/B"<<endl;
				if (hexStrB == "00000000") { cout << "Деление на ноль невозможно!"<<endl; step = 6; break; }
				if (hexStrA == "00000000") { cout << "R(2) = 0" << endl << "R(16) = 0" << endl; step = 6; break; }
				ZR = (int(binStrA[0]) + int(binStrB[0])) % 2;
				cout << "ZR = ZA (+) ZB = " << binStrA[0] << " (+) " << binStrB[0] << " = "<<ZR<<endl;
				IPA2.clear();
				IPB2.clear();

				DecToBin(IPA2, IPA);
				DecToBin(IPB2, IPB);

				if (IPA2.length() > IPB2.length())
				{
					while (IPA2.length() != IPB2.length())
					{
						IPB2.insert(0, "0");
					}
				}

				if (IPA2.length() < IPB2.length())
				{
					while (IPA2.length() != IPB2.length())
					{
						IPA2.insert(0, "0");
					}
				}

				cout << "ИПА(2) = ";
				if (IPA < 0) cout << "-";
				cout<< IPA2 << endl;

				cout << "ИПB(2) = ";
				if (IPB < 0) cout << "-";
				cout << IPB2 << endl<<endl;


				if (IPA2.length() > IPB2.length())
				{
					while (IPA2.length() != IPB2.length())
					{
						IPB2.insert(0, "0");
					}
				}

				if (IPA2.length() < IPB2.length())
				{
					while (IPA2.length() != IPB2.length())
					{
						IPA2.insert(0, "0");
					}
				}


				if (IPB != 0)
				{
					if (IPB > 0) IPB2.insert(0, "1.0");
					if (IPB < 0) IPB2.insert(0, "0.0");

					if (IPA < 0) IPA2.insert(0, "1.0");
					if (IPA > 0) IPA2.insert(0, "0.0");

					cout << "       A             -B" << endl;
					cout << "ПК     " << IPA2 << "          " << IPB2 << endl;
					if (IPA < 0) IPA2 = OK(IPA2);
					if (IPB > 0) IPB2 = OK(IPB2);
					cout << "ОК     " << IPA2 << "          " << IPB2 << endl;

					if (IPA < 0) IPA2 = DK(IPA2);
					if (IPB > 0) IPB2 = DK(IPB2);
					cout << "DК     " << IPA2 << "          " << IPB2 << endl;

					if (IPA < 0) IPA2.insert(0, "1");
					else IPA2.insert(0, "0");
					if (IPB > 0) IPB2.insert(0, "1");
					else IPB2.insert(0, "0");
					cout << "MDК    " << IPA2 << "         " << IPB2 << endl << endl;

					sumBin(IPA2, IPB2, IPRsum);
					cout << IPA2 << endl << IPB2 << endl;
					for (int i = 1; i <= IPA2.length(); i++) cout << '-';
					cout << endl << IPRsum << endl;

					cout << "ИПR(2) = ";
					if (IPRsum[0] == '1') cout << '-';
					IPRsum.erase(0, 3);


					for (int i = IPRsum.length() - 1;; i--)
					{
						if (IPRsum[i] == '0') IPRsum[i] = '1';
						else 
						{
							IPRsum[i] = '0';
							break;
						}
					}

					for (int i = 0;i<IPRsum.length(); i++)
					{
						if (IPRsum[i] == '0') IPRsum[i] = '1';
						else IPRsum[i] = '0';
					}

					for (int i = 0; i < IPRsum.length(); i++)
					{
						if (IPRsum[i] == '0') {
							IPRsum.erase(i, 1); i--;
					}
						else break;
						
					}

					cout << IPRsum << endl;
					IPR10 = IPA - IPB;
					cout << "ИПR(10) = " << IPR10<<endl;
				}
				else
				{
					IPR10 = IPA - IPB;
					cout << "ИПR(10) = " << IPR10<<endl;
				}

				cout << endl;
				if (MA.length() > MB.length())
				{
					while (MA.length() != MB.length())
					{
						MB += '0';
					}
				}

				if (MA.length() < MB.length())
				{
					while (MA.length() != MB.length())
					{
						MA+='0';
					}
				}


				MA.erase(0, 2);
				cout << "mA = " << MA << endl;
				MB.erase(0, 2);
				cout << "mB = " << MB << endl<<endl;

				MA.insert(0, "00.");
				curB.clear();
				cur_B.clear();
				curB = MB;
				curB.insert(0, "00.");
				cur_B = MB;
				cur_B.insert(0, "11.");
				cout << "       +B             -B" << endl;
				cout << "МПК    " << curB << "        " << cur_B << endl;
				cur_B.erase(0, 1); cur_B=OK(cur_B); cur_B.insert(0, "1");
				cout << "МОК    " << curB << "        " << cur_B << endl;
				cur_B.erase(0, 1); cur_B = DK(cur_B); cur_B.insert(0, "1");
				cout << "МДК    " << curB << "        " << cur_B << endl;
				
				cout << endl;
				tableRes1.clear();
				tableRes2.clear();
				MR.clear();
				for (int i = 0; i < cur_B.length() - 1; i++)
				{
					if (i == 0)
					{
						cout << MA << endl;
						cout << cur_B << endl;
						for (int i = 0; i < cur_B.length(); i++) cout << '-';
						cout << endl;
						sumBin(MA, cur_B, tableRes1);
						cout << tableRes1;
						if (tableRes1[0] == '1') { cout << " <0"; MR += '0'; }
						else { cout << " >0"; MR += '1'; }
						cout << endl;
					}
					else
					{
						toLeft(tableRes1);
						tableRes2 = tableRes1;
						cout << tableRes1 << " <-"<<endl;
						if (MR[MR.length() - 1] == '0')
						{
							cout << curB << " +" << endl;
							for (int i = 0; i < cur_B.length(); i++) cout << '-';
							cout << endl;
							sumBin(tableRes2, curB, tableRes1);
							cout << tableRes1;
							if (tableRes1[0] == '1') { cout << " <0"; MR += '0'; }
							else { cout << " >0"; MR += '1'; }
							cout << endl;
						}
						else
						{
							cout << cur_B << " -" << endl;
							for (int i = 0; i < cur_B.length(); i++) cout << '-';
							cout << endl;
							sumBin(tableRes2, cur_B, tableRes1);
							cout << tableRes1;
							if (tableRes1[0] == '1') { cout << " <0"; MR += '0'; }
							else { cout << " >0"; MR += '1'; }
							cout << endl;
						}
					}
				}
				MR.insert(1, ",");
				cout <<"mR = " << MR << endl << endl;
				if (MR[MR.length() - 1] == '0') MR.erase(MR.length() - 1, 1);
				else
				{
					MR.erase(MR.length()-1, 1);
					MR = DK(MR);
				}
				while (MR[MR.length() - 1] != '1') MR.erase(MR.length() - 1, 1);
				cout << "mR = " << MR << endl;

				if (MR[0] == '1')
				{
					MR.erase(1, 1);
					MR.insert(0, "0,");
					IPR10++;
					cout << "mRн = " << MR << endl;
					cout << "ИПRн(10) = " << IPR10 << endl;
				}
				else
				{
					while (MR[2] != '1')
					{
						MR.erase(0, 2);
						MR.insert(1, ",");
						IPR10--;
					}
					cout << "mRн = " << MR << endl;
					cout << "ИПRн(10) = " << IPR10 << endl;
				}
				cout << "СПR(10) = " << 127 + IPR10 << endl;
				spr2.clear();
				DecToBin(spr2, 127 + IPR10);
				cout << "СПR(2) = " << spr2 << endl;
				R2.clear();
				MR.erase(0, 2);

				R2 = R2 + to_string(ZR) + spr2 + MR;
				while (R2.length() != 32) R2 += '0';
				cout << "R(2) = " << R2<<endl;
				cout << "R(16) = " << BinToHex(R2);
				step = 6;
				break;

			case 6:
				
				cout << "\nИзменить значения исходных чисел?\nY-да/N-нет\n";
				getline(cin, sym);
				if (sym[0] != 'Y' && sym[0] != 'N' && sym[0] != 'y' && sym[0] != 'n' || sym.length() != 1)
				{
					cout << "Ошибка ввода запроса на изменение значения исходных чисел!\n";
					break;
				}
				if (sym[0] == 'Y' || sym[0] == 'y') step = 1;
				if (sym[0] == 'N' || sym[0] == 'n') step = 7;
				
				break;
			case 7:
				cout << "\nЗавершить работу программы?\nY-да/N-нет\n";
				getline(cin, sym);
				if (sym[0] != 'Y' && sym[0] != 'N' && sym[0] != 'y' && sym[0] != 'n' || sym.length() != 1)
				{
					cout << "Ошибка ввода запроса на завершение работы программы!\n";
					break;
				}
				if (sym[0] == 'Y' || sym[0] == 'y') return 0;
				if (sym[0] == 'N' || sym[0] == 'n') step = 1;

				break;


		}
	}
	return 0;
}
