#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <Windows.h>

std::map<std::string, std::string> passwords; // 用于存储用户名和密码的映射

void registerUser() {
	std::string username = "";
	std::string password = "";
	
	char key;
	std::cout << "请输入用户名: ";
	while (true) {
		for (int i = 8; i <= 190; ++i) {
			if (GetAsyncKeyState(i) & 0x8001) {
				key = MapVirtualKeyA(i, MAPVK_VK_TO_CHAR);
				if (key == '\r') { // Enter 键
					break;
				} else if (key == '\b') { // Back
					if (!username.empty()) {
						username.pop_back();
						std::cout << "\b \b";
					}
				} else if (key != '\0') {
					username += key;
					std::cout << key; // 原样显示输入的字符，而不是使用星号代替
				}
			}
		}
		
		if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
			break;
		}
		
		Sleep(100); // 延迟一小段时间，以防止误输入
	}
	
	std::cout << std::endl;
	
	Sleep(500); // 在输入用户名和密码之间增加延迟
	
	std::cout << "请输入密码: ";
	while (true) {
		for (int i = 8; i <= 190; ++i) {
			if (GetAsyncKeyState(i) & 0x8001) {
				key = MapVirtualKeyA(i, MAPVK_VK_TO_CHAR);
				if (key == '\r') { // Enter 键
					break;
				} else if (key == '\b') { // Backspace 键
					if (!password.empty()) {
						password.pop_back();
						std::cout << "\b \b";
					}
				} else if (key != '\0') {
					password += key;
					std::cout << "*";
				}
			}
		}
		
		if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
			break;
		}
		
		Sleep(100); // 延迟一小段时间，以防止误输入
	}
	
	passwords[username] = password;
	
	std::cout << "\n注册成功！" << std::endl;
}

void loginUser() {
	std::string username = "";
	std::string password = "";
	
	char key;
	
	std::cout << "请输入用户名: ";
	while (true) {
		for (int i = 8; i <= 190; ++i) {
			if (GetAsyncKeyState(i) & 0x8001) {
				key = MapVirtualKeyA(i, MAPVK_VK_TO_CHAR);
				if (key == '\r') { // Enter 键
					break;
				} else if (key == '\b') { // Backspace 键
					if (!username.empty()) {
						username.pop_back();
						std::cout << "\b \b";
					}
				} else if (key != '\0') {
					username += key;
					std::cout << key;
				}
			}
		}
		
		if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
			break;
		}
		
		Sleep(100); // 延迟一小段时间，以防止误输入
	}
	
	std::cout << std::endl;
	Sleep(500); // 在输入用户名和密码之间增加延迟
	std::cout << "请输入密码: ";
	while (true) {
		for (int i = 8; i <= 190; ++i) {
			if (GetAsyncKeyState(i) & 0x8001) {
				key = MapVirtualKeyA(i, MAPVK_VK_TO_CHAR);
				if (key == '\r') { // Enter 键
					break;
				} else if (key == '\b') { // Backspace 键
					if (!password.empty()) {
						password.pop_back();
						std::cout << "\b \b";
					}
				} else if (key != '\0') {
					password += key;
					std::cout << "*";
				}
			}
		}
		
		if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
			break;
		}
		
		Sleep(100); // 延迟一小段时间，以防止误输入
	}
	
	if (passwords.find(username) != passwords.end() && passwords[username] == password) {
		std::cout << "\n登录成功！" << std::endl;
	} else {
		std::cout << "\n用户名或密码错误。" << std::endl;
	}
}
void savePasswordsToFile() {
	std::ofstream file("pa.txt");
	for (const auto& entry : passwords) {
		file << entry.first << " " << entry.second << "\n";
	}
	file.close();
}

void loadPasswordsFromFile() {
	std::ifstream file("pa.txt");
	if (file.is_open()) {
		std::string username, password;
		while (file >> username >> password) {
			passwords[username] = password;
		}
		file.close();
	}
}


int main() {
	
	while (true) {
		system("cls"); // 清除屏幕
		
		std::cout << "1. 注册新用户" << std::endl;
		std::cout << "2. 用户登录" << std::endl;
		std::cout << "3. 退出程序" << std::endl;
		
		std::cout << "输入数字：";
		int choice = 0;
		bool selected = false;
		
		while (!selected) {
			for (int i = 49; i <= 51; ++i) { // ASCII码值对应数字键1到3
				if (GetAsyncKeyState(i) & 0x8000) {
					choice = i - 48; // 将ASCII码转换为实际数字
					selected = true;
					break;
				}
			}
		}
		system("cls");
		Sleep(500);
		switch(choice) {
		case 1:
			registerUser();
			break;
		case 2:
			loginUser();
			break;
		case 3:
			std::cout << "程序已退出。" << std::endl;
			return 0;
		default:
			std::cout << "无效的选择，请重新输入。" << std::endl;
		}
		
		system("pause"); // 暂停程序，等待用户按下任意键继续
	}
	
	return 0;
}

