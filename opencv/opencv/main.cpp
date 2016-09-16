# include "Operator.h"


int main(int argc, char **argv) {
	auto ope = make_unique<Operator>();

	ope->exec();

	return 0;
}