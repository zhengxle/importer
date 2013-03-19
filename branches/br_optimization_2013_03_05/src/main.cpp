/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  12/24/12 15:04:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiaoliang (zxl), xiaoliang.zxl@taobao.com
 *        Company:  Taobao.com
 *
 * =====================================================================================
 */

#include <getopt.h>
#include <stdio.h>
#include <tools/Log.h>
#include <tbsys.h>  // include tbsys.h to setLogLevel for tair
#include "Config.h"
#include "Importer.h"
void usage(const char *cmd)
{
    printf("usage: %s [<options>]\n",cmd);
    printf("Where <options> are: \n");
    printf("  -f <filename>\t\tthe file to import, key-value pair is splited by ^D,\n" 
            "\t\t\ttwo key-value pairs splited by -S arguments, default is '\\n'\n");
    printf("  -p <pbfilename>\tthe protobuf serialized file, key-value pair is \n"
            "\t\t\tprefix with size, like that \"keysize key valuesize value\"\n");
    printf("  -a <area>\t\tnamespace to import\n");
    printf("  -m <master addr>\tmaster configserver addr [ip:port], default port is 5198\n");
    printf("  -s <slave addr>\tslave configserver addr [ip:port], default port is 5198\n");
    printf("  -g <group>\t\tgroup name\n");
    printf("  -c <concurrency>\tNumber of thread to import, default is 1\n");
    printf("  -r <repeat numbers>\trepeat numbers to put to tair, default is 3\n");
    printf("  -e <expire>\t\texpire time, default will never expire\n");
    printf("  -K <key value seperate character>, default is '^D'\n");
    printf("  -M <numBeforeSleep>\tafter import numBeforeSleep key-value pairs, sleep 1s. default is 1,000,000\n");
    printf("  -S <items seperate character> default is '\\n' \n");
    printf("  -v <version>\t\tif version > 0, using enhanced version, else using the old version\t\n");
    printf("  -h <help>\t\n");
}

enum {
    REPEAT_NUM = 3,
};

bool parseCommandOption(int argc, char *argv[], Config &config)
{
	int c;
	#ifdef NDEBUG
    config.configFile = "/home/a/share/tools/tairFileImporter/conf/importer.conf";
#else
    config.configFile = "./importer.conf";
#endif
	while ((c = getopt(argc,argv,"f:p:a:m:s:S:g:c:r:e:M:K:vh")) != -1) {
		switch (c) {
			case 'f':
				config.fileName = optarg;
				break;
            case 'p':
                config.pbFileName = optarg;
                break;
			case 'a':
				config.tairArea = atoi(optarg);
				break;
			case 'm':
				config.master = optarg;
				break;
			case 's':
				config.slave = optarg;
				break;
			case 'g':
				config.group = optarg;
				break;
			case 'c':
				config.threadNum = atoi(optarg);
				break;
			case 'r':
				config.repeatNum = atoi(optarg);
				break;
			case 'e':
				config.expireTime = atoll(optarg);
				break;
            case 'K':
                config.kvSep = atoi(optarg);
                break;
			case 'M':
				config.maxNumSleep = atoi(optarg);
				break;
			case 'v':
				printf("tair import client : version 1.0.0\n");
				exit(0);
			case 'h':
				usage(argv[0]);
				exit(0);
            case 'S':
                config.itemSep = atoi(optarg);
                break;
			default:
				usage(argv[0]);
				return false;
		}
	}
	return true;
}

int main(int argc, char *argv[])
{
    TBSYS_LOGGER.setLogLevel("ERROR");
	Config config;
	if (!parseCommandOption(argc, argv, config)) {
		usage(argv[0]);
        return -1;
    }
    if (!config.load(config.configFile)) {
        return false;
    }

    LOG_INIT(config.logFile.c_str());
    Importer importer;
    if (!importer.init(config)) {
        return -1;
    }

    return importer.process(config);
}
