����������
Win7 32bit��qt-opensource-windows-x86-mingw492-5.5.0


VC�����ÿ��ļ�Ϊxxx.lib�� GCC��Ϊxxx.a��ͨ���Ƚ����ֿ��ļ��ĸ�ʽ�����ֺ����ơ����ǰ�xxx.dll��xxx.lib��xxx.h���Ƶ�Qt��project�£�ֱ�Ӱ�xxx.lib��Ϊxxx.a, ����Qt�Ŀ����ֵĸ�ʽ�� ��xxx.a��ǰ�����lib�� ��Ϊlibxxx.a��
����Qt��.pro�ļ�����������
LIBS += -L. �Clxxx  //���ӵ�ǰĿ¼�µ�libxxx.a

����pro�ļ��м���һ�У�
LIBS += -L ./ -lPlotDll
Ȼ��PlotDll.dll��PlotDll.lib����������buildĿ¼�£����Ǻ���Makefile��Ŀ¼���������±���һ�Σ�Ӧ�þͿ�����