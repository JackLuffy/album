#include "common.h"
#include "ts.h"
#include "lcd.h"

#define LIST_NODE_DATATYPE filenode
#include "list.h"

char *check_args(int argc, char **argv)
{
	if(argc >= 3)
	{
		fprintf(stderr, "invalid arguments\n");
		fprintf(stderr, "Usage: %s [file][directory]\n", argv[0]);

		exit(0);
	}

	return argc==2 ? argv[1] : ".";
}

bool is_jpg(char *filename)
{
	assert(filename);

	// check the filename contains the specified suffix
	char *tmp1 = strstr(filename, ".jpg");
	char *tmp2 = strstr(filename, ".jpeg");

	if(tmp1 == NULL && tmp2 == NULL)
	{
		return false;	
	}

	if(tmp1 != NULL && strlen(tmp1) > strlen(".jpg") ||
	   tmp2 != NULL && strlen(tmp2) > strlen(".jpeg") )
	{
		return false;
	}

	return true;
}

char *decompress_jpg(char *jpgname)
{
	return "";
}

void display(char *rgb)
{

}

void show_jpg(char *filename)
{
	assert(filename);

	char *rgb = decompress_jpg(filename);
	display(rgb);
}

void show_jpg_dir(char *dirname)
{
	assert(dirname);

	DIR *dp = opendir(dirname);
	if(dp == NULL)
	{
		fprintf(stderr, "open %s failed: %s\n",
				dirname, strerror(errno));
		return;
	}

	// enter the directory
	chdir(dirname);

	struct dirent *ep = NULL;
	struct stat finfo;
	while(1)
	{
		if((ep=readdir(dp)) == NULL)
		{
			break;
		}

		bzero(&finfo, sizeof(finfo));
		stat(ep->d_name, &finfo);

		if(!S_ISREG(finfo.st_mode) || !is_jpg(ep->d_name))
			continue;

		show_jpg(ep->d_name);

		wait4touch(100);
	}
}


int main(int argc, char **argv)
{
	char *file = check_args(argc, argv);

	// get file's infomation
	struct stat finfo;
	bzero(&finfo, sizeof(finfo));
	stat(file, &finfo);

	// prepare LCD
	lcdinfo *linfo = init_lcd();

	// prepare the double-link list
	linklist head = init_list();

	if(S_ISREG(finfo.st_mode) && is_jpg(file))
	{
		show_jpg(file);
	}
	else if(S_ISDIR(finfo.st_mode))
	{
		show_jpg_dir(file);	
	}
	else
	{
		fprintf(stderr, "only regular or directory accepted.\n");
		fprintf(stderr, "bye bye!.\n");
	}

	return 0;
}
