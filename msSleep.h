inline void msSleep(unsigned int ms)
{
#ifdef _WIN32
	Sleep(ms);
#else
	struct timespec ts;
	if(ms==0){__asm__("rep\n\t" "nop");}
	else
	{
		ts.tv_sec=ms/1000;
		ts.tv_nsec=ms%1000*1000000;
	}
	nanosleep(&ts, NULL);
#endif
}
