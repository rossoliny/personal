
void func(char*, int&) {
	
}
void (*funcP)(char*, int&) = func;


void accept_funcP(void (*funP)(char*, int&));

void (*ret_funcP())(char*, int&);

// typedef void (*fp_t)(char*, int&);

void (*accept_ret_funcP(void (*funcP)(char*, int&))) (char*, int&);

int main (int argc, char** argv) 
{

	return 0;
	
}


