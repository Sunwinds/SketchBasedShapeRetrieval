#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QtGui/QMainWindow>
#include "ui_workspace.h"
#include <QtGui>
#include <QStringList>
#include <QVector>
#include <vector>

#include "../Features/include/felib.h"

#include "../MeshViewer/QuickMeshViewer.h"
#include "scribbleboard.h"

#define Min(a,b) ((a)<(b)?(a):(b))

#define MAXLENGTH 10000

#define CONFIGPATH "Config"
#define FEATUREFILE "features.csv"

class RetrData 
{
public:
	//Current distance to the query data
	double dist;
	//Initial of line rendering corresponding to its 3D shape.
	QString initial;
	//Image file
	imgFile img;
	//Feature vector
	double *feaVec; 

public:
	RetrData();
	RetrData(double mdist, QString& mInit, imgFile& mImg, double *fvec);
	~RetrData();
};

bool cmpfunc(const RetrData &lhs, const RetrData &rhs);

class WorkSpace : public QMainWindow
{
	Q_OBJECT

public:
	WorkSpace(QWidget *parent = 0, Qt::WFlags flags = 0);
	~WorkSpace();

    QString selectedFile();

	//Data online
	std::vector<RetrData> dataset;
	//Data backup
	std::vector<RetrData> srcData;

	int gaborOpt[4], gistOpt[4];
	double wght[4];
	int* flen;

	//Current Sketch
	imgFile *curSketch;

private:
	Ui::WorkSpaceClass ui;
	
	ScribbleBoard *scribbleboard;

	QVector< QVector<QuickMeshViewer*> > viewers;
	QuickMeshViewer* activeViewer;

	//All line renderings in the dataset
	//std::vector<imgFile *> imglist;

	QString imagePath;
	QString shapePath;
	QStringList files;

	//Set of features
	std::vector<double *> feaSet;

	int countX, countY;
	int numActiveViewers;

	void createAction();

	bool maybeSave();
	bool saveFile(const QByteArray &fileFormat);
	
	/*****************Retrieval*******************/
	//Initialize the engine
	void initEngine();
	//Load configuration parameter from file
	bool loadParam(const QString &mFile);
	//Truncate path to get the name of corresponding shape
	void get3Dfn(const QString& src, const QString& refChar,QString& res);
    //Calculate distance between images
	double imgDistance(imgFile *img1, imgFile *img2);
	//Calculate distance between two feature vectors
	double imgDistance(double *lhs, double *rhs);
    //Rank the result based on distances
	void rankResults();
	bool isInlist(QVector<QString> &mlist, QString &ini);
	//Select the top 20 to show
    void updateFileList();
	//Calculate feature vector for current sketch.
	double* calFeature();

protected:
	virtual void showEvent(QShowEvent * event);

private slots:
	/**************Sketch Interface****************/
	void open();
	void save();
	void clear();
	void about();
	void genofflineData();

public slots:
	void loadMeshes(QString using_path);
	void loadMeshes();
	void loadMeshes(QStringList& filelist);
	void showNumViewers(int n);
	void loadCurrentMeshes();
	void setActiveViewer(QuickMeshViewer*);
	void refresh();
	void search();
	

};

#include <QThread>
class LoaderThread : public QThread{
	Q_OBJECT
public:
	LoaderThread(QuickMeshViewer *, QString);
	QuickMeshViewer * viewer;
	QString fileName;
protected:
	void run();
};

#endif // WORKSPACE_H
