#include "Calculator.h"

#include "Application.h"

namespace Calculator {
	void run() {
		Application app;

		while (app.isRunning()) {
			app.getPrompt();
			app.handlePrompt();
		}
	}
}