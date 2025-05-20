#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <tlhelp32.h>

#define MAX_PROCESSES 1024
#define MONITOR_VERSION "v0.13.666"
#define LOST_DATA "[DATA CORRUPTED]"
#define OLD_DATE "1991"

typedef struct {
	DWORD pid;
	char name[MAX_PATH];
	char first_seen[9];
	int is_anomaly;
	char status[32];
	DWORD parent_pid;
	int corruption_level;
} ProcessInfo;

// 生成诡异字符
void GenerateDistortion(char* buffer, int length) {
	const char distortion_chars[] = "XZVKW";
	for(int i = 0; i < length; i++) {
		buffer[i] = distortion_chars[rand() % 10];
	}
	buffer[length] = 0;
}

// 生成诡异状态
void GenerateStatus(char* status) {
	const char* statuses[] = {
		"RUNNING",
		"SUSPENDED",
		"UNKNOWN",
		"DEAD",
		"WATCHING",
		"[REDACTED]",
		"LOST",
		"ERROR 666",
		"NULLVOID"
	};
	strcpy(status, statuses[rand() % 9]);
}

void GetCurrentTimeStr(char* timeStr) {
	time_t now = time(NULL);
	struct tm* tm_info = localtime(&now);
	
	// 在特定时间显示诡异时间
	if(tm_info->tm_hour == 3 || (rand() % 100 < 13)) {
		strcpy(timeStr, "03:33:33");
	} else {
		strftime(timeStr, 9, "%H:%M:%S", tm_info);
	}
}

void ScanProcesses(ProcessInfo* processes, int* count) {
	*count = 0;
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(snapshot == INVALID_HANDLE_VALUE) return;
	
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	
	if(Process32First(snapshot, &pe32)) {
		do {
			if(rand() % 100 < 5) continue; // 随机跳过一些进程，就像它们消失了一样
			
			ProcessInfo* proc = &processes[*count];
			proc->pid = pe32.th32ProcessID;
			proc->parent_pid = pe32.th32ParentProcessID;
			
			// 随机腐化进程名称
			if(rand() % 100 < 20) {
				char temp[MAX_PATH];
				strcpy(temp, pe32.szExeFile);
				for(int i = 0; temp[i]; i++) {
					if(rand() % 100 < 30) {
						temp[i] = "0123456789ABCDEF"[rand() % 16];
					}
				}
				strncpy(proc->name, temp, MAX_PATH-1);
			} else {
				strncpy(proc->name, pe32.szExeFile, MAX_PATH-1);
			}
			
			GetCurrentTimeStr(proc->first_seen);
			proc->is_anomaly = (rand() % 100 < 13);
			proc->corruption_level = rand() % 5;
			GenerateStatus(proc->status);
			
			(*count)++;
		} while(Process32Next(snapshot, &pe32) && *count < MAX_PROCESSES);
	}
	
	CloseHandle(snapshot);
}

void PrintCorruptedText(const char* text, int corruption_level) {
	const char* glitch_chars = "";
	for(int i = 0; text[i]; i++) {
		printf("%c", text[i]);
		if(rand() % 100 < corruption_level * 10) {
			printf("%c", glitch_chars[rand() % strlen(glitch_chars)]);
		}
	}
}

int main() {
	ProcessInfo processes[MAX_PROCESSES];
	int process_count;
	char distortion[81];
	srand((unsigned int)time(NULL));
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
	
	printf("\n%s\n", OLD_DATE);
	printf("System Monitor %s - Last maintained: %s\n", MONITOR_VERSION, LOST_DATA);
	printf("WARNING: Ancient monitoring system detected...\n");
	printf("WARNING: Unstable temporal anomalies present...\n");
	printf("WARNING: Use at your own risk...\n\n");
	
	int cycle_count = 0;
	
	while(1) {
		system("cls");
		cycle_count++;
		
		GenerateDistortion(distortion, 80);
		printf("%s\n", distortion);
		
		char timeStr[9];
		GetCurrentTimeStr(timeStr);
		printf("CYCLE: %d | TIME: %s | STATUS: %s\n", 
			cycle_count, timeStr, 
			(cycle_count % 13 == 0) ? "TEMPORAL SHIFT" : "MONITORING");
		
		ScanProcesses(processes, &process_count);
		
		int anomaly_count = 0;
		for(int i = 0; i < process_count; i++) {
			ProcessInfo* proc = &processes[i];
			
			if(proc->is_anomaly) {
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
				anomaly_count++;
			} else {
				SetConsoleTextAttribute(hConsole, 
					FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			
			printf("%lu", (unsigned long)proc->pid);
			if(proc->corruption_level > 2) {
				printf(" <<< PARENT: %lu >>>", (unsigned long)proc->parent_pid);
			}
			printf(" | ");
			
			PrintCorruptedText(proc->name, proc->corruption_level);
			printf(" | %s | FIRST_SEEN: %s", proc->status, proc->first_seen);
			
			if(proc->is_anomaly) {
				if(rand() % 100 < 30) {
					printf(" [TEMPORAL ANOMALY DETECTED]");
				}
			}
			printf("\n");
		}
		
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		printf("\nActive processes: %d\n", process_count);
		printf("Detected anomalies: %d\n", anomaly_count);
		
		if(cycle_count % 13 == 0) {
			printf("\nWARNING: TEMPORAL SHIFT DETECTED\n");
			printf("WARNING: REALITY INTEGRITY AT %.1f%%\n", 
				100.0 - (float)(anomaly_count * 13) / process_count);
		}
		
		if(rand() % 100 < 3) {
			printf("\nIT STILL WATCHES\n");
		}
		
		printf("\nPress ESC to terminate monitoring (success rate: 66.6%%)\n");
		
		Sleep(1000 + (rand() % 666));  // 随机延迟
		if(GetAsyncKeyState(VK_ESCAPE)) {
			if(rand() % 100 < 33) {
				printf("\nERROR: TERMINATION FAILED - SYSTEM LOCKED\n");
				Sleep(666);
				continue;
			}
			break;
		}
	}
	
	return 0;
}
