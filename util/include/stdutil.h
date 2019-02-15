#pragma once


#include "UnionConfig.h"
#include "SerialLibrary.h"

#include <thread>
#include <fstream>

#ifdef _WIN32
#include <time.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#define CRS_SOCKET SOCKET
#define CRS_INVALID_SOCKET INVALID_SOCKET
#define CRS_SOCKET_ERROR SOCKET_ERROR
#elif __linux__
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define CRS_SOCKET int
#define CRS_INVALID_SOCKET -1
#define CRS_SOCKET_ERROR -1
#endif
#define BUFFER_SIZE 512

namespace mammoth{
	namespace layer {
		class FileUtil {
		public:
			//0 read-only 1 append 2 write 
			FileUtil(const char * path, unsigned open_mode);
			~FileUtil();
			std::string read_line();
			void write_line(const std::string & content, bool new_line = true);
			static void get_all_files(std::string path, std::vector<std::string>& files);
		private:
			std::ofstream * out_file_stream_ptr;
			std::ifstream * in_file_stream_ptr;
		};

		class SerialUtil {
		public:
			static void openAsync(const char * serial, int baut_rate, void(*read_func)(const std::string& data, void* context));
			static SyncCom openSync(const char * serial, int baut_rate);
			static void close();
			static void read_gps(const std::string& data, void* context);
			static void write(ASynCom* com, const std::string& msg, int* cont);
		};

		class ThreadUtil {
		public:
			static std::thread create_thread(void(*thread_func)());
			static void join(std::thread& thread);
			static void kill(std::thread& thread);
		};

		class ConvertUtil {
		public:
			static std::string itoa(const int& number);
			static int atoi(const std::string& str);
			static float string2float(const std::string& str);
			static bool AddressConvert(const std::string& src, std::string& ip, unsigned short& port);
			static bool SplitString(const std::string& str, const std::string& pattern, std::vector<std::string>& strlist);
			static void ConvertToWord(const unsigned char & low, const unsigned char & high, unsigned short & word);
			
			template<typename TSRC, typename TDEST>
			static TDEST ConvertTo(const TSRC & data) {
				std::stringstream ss;
				ss << data;
				TDEST res;
				ss >> res;
				return res;
			}
		};

		class TcpClient {
		public:
			TcpClient() : m_transform(nullptr), m_sockFd(-1), m_isConnected(false) {}
			~TcpClient();
			bool Init();
			bool Connect(const char * addr, const unsigned short & servicePort);
			bool DisConnect();
			bool IsConnected() { return m_isConnected; }
			char * m_transform;
			int m_transLength;
			// transform command
			bool Recv(std::string& msg);
			bool Send(const std::string& msg);
		private:
			int m_sockFd;
			struct sockaddr_in m_servAddr;
			bool m_isConnected;
			unsigned short m_bufferLength;
		};

		class UdpServer {
		public:
			UdpServer() : m_sockFd(CRS_INVALID_SOCKET) {}
			~UdpServer() { Release(); }
			bool Init();
			bool Bind(const unsigned short & servicePort);
			bool Release();
			bool SendTo(const char * data, const size_t & length, const char * clientIp, const int & port);
			bool RecvFrom(char * data, size_t & length, char ** ppaddr, unsigned short * pport);
			bool RecvFrom(std::string & msg);
		private:
			CRS_SOCKET m_sockFd;
			struct sockaddr_in m_servAddr;
			struct sockaddr_in m_sendAddr;
			char m_buffer[512];
			size_t m_bufferLength;
		};

		enum TIME_ITEM { YEAR, MONTH, DATE, HOUR, MINUTE, SECOND, DAY, MILLSECOND };
		class TimeUtil {
		public:
			static std::string get_time_str();
			static int get_time(const TIME_ITEM&);
			static std::string get_time_code();
			static std::string get_time_code_millsecond();
		private:
			static SYSTEMTIME sys_time;

		};

	}
}