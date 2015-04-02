#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

class ApplicationState;

class ApplicationManager
{
public:
	ApplicationManager();

	void initialize() { };
	void update() { };
	void render() { };

private:
	int m_activeState;
};

#endif