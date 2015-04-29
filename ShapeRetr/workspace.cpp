#include "workspace.h"
#include <cmath>
#include <algorithm>
#include <functional>
#include <string>
#include <fstream>
#include <sstream>

#include "../Features/include/extractFeatures.h"
#include "../Features/include/extractFeatures.c"
#include "../IO/DataFile.h"


/******************RetrData*******************/
RetrData::RetrData()
{
	dist = 0.0;
	initial = "";
	img.id = 0;
	img.fname = NULL;
	feaVec = NULL;
}

RetrData::RetrData(double mdist, QString& mInit, imgFile& mImg,  double *fvec)
{
	dist = mdist;
	initial = mInit;
	img = mImg;
	feaVec = fvec;
}

RetrData::~RetrData()
{
	img.fname = NULL;
	feaVec = NULL;
}

bool cmpfunc(const RetrData &lhs, const RetrData &rhs)
{
	return ( lhs.dist < rhs.dist ); 
}

/******************Workspace******************/

WorkSpace::WorkSpace(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	scribbleboard = new ScribbleBoard(ui.formLayoutWidget);
    scribbleboard->setGeometry(0,0,500,400);

	countX = 3;
	countY = 3;

	viewers.resize(countX);
	for(int i = 0; i < countX; i++){
		viewers[i].resize(countY);
		for(int j = 0; j < countY; j++){
			viewers[i][j] = new QuickMeshViewer;
			connect(viewers[i][j], SIGNAL(gotFocus(QuickMeshViewer*)), SLOT(setActiveViewer(QuickMeshViewer*)));
		}
	}

	numActiveViewers = 0;
	activeViewer = viewers[0][0];

	for(int i = 0; i < countX; i++)
		for(int j = 0; j < countY; j++)
		    ui.thumbLayout_2->addWidget(viewers[i][j], i, j);

	// Default path
	//path = "D:\\Projects\\3d-workspace\\data";

	loadMeshes("D:\\Projects\\SktShpRetrieval\\ShapeRetr\\Data\\Shapes");
	imgFile *tmpImg;
	tmpImg->id = 0;
	tmpImg->fname = "D:\\Projects\\SktShpRetrieval\\ShapeRetr\\Data\\tmp.png";
	curSketch = tmpImg;

	initEngine();

    createAction();
}

WorkSpace::~WorkSpace()
{
	if(scribbleboard)
		delete scribbleboard;
	if(activeViewer)
        activeViewer = NULL;
	if (viewers.size())
	{
		for(int i = 0; i < countX; i++){
			for(int j = 0; j < countY; j++){
				delete viewers[i][j];
			}
			viewers[i].resize(0);
		}
		viewers.resize(0);
		viewers.clear();
	}
    
	/*free(gaborOpt);
	free(gistOpt);
	free(wght);
	free(flen);*/
}

void WorkSpace::createAction()
{
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(open()));
	connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(save()));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));
	connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(about()));
	connect(ui.actionGenData, SIGNAL(triggered()), this, SLOT(genofflineData()));
	connect(ui.mOpen, SIGNAL(clicked()), this, SLOT(open()));
	connect(ui.mSave, SIGNAL(clicked()), this, SLOT(save()));
	connect(ui.mClear, SIGNAL(clicked()), this, SLOT(clear()));

	connect(ui.scrollBar_2, SIGNAL(valueChanged(int)), SLOT(loadMeshes()));
	connect(ui.mSearch, SIGNAL(clicked()), this, SLOT(search()));
}

/********************Sketch Interface********************/
void WorkSpace::open()
{
	if (maybeSave()) {
		QString fileName = QFileDialog::getOpenFileName(this,
			tr("Open File"), QDir::currentPath());
		if (!fileName.isEmpty())
			scribbleboard->openImage(fileName);
	}
}

void WorkSpace::save()
{
	QAction *action = qobject_cast<QAction *>(sender());
	QByteArray fileFormat = action->data().toByteArray();
	saveFile(fileFormat);
}

void WorkSpace::clear()
{
	scribbleboard->clearImage();
}

void WorkSpace::about()
{
	QMessageBox::about(this, tr("About SkeShpRetr"),
		tr("<p>The <b>SkeShpRetr</b> is an implementation of sketch based 3D shape retrieval</p> "
		"<p> Created by <b>Shuyang Sun</b></p>"
		"<p>shuyangs@sfu.ca</p>"));
}


bool WorkSpace::maybeSave()
{
	if (scribbleboard->isModified()) {
		QMessageBox::StandardButton ret;
		ret = QMessageBox::warning(this, tr("Scribble"),
			tr("The image has been modified.\n"
			"Do you want to save your changes?"),
			QMessageBox::Save | QMessageBox::Discard
			| QMessageBox::Cancel);
		if (ret == QMessageBox::Save) {
			return saveFile("png");
		} else if (ret == QMessageBox::Cancel) {
			return false;
		}
	}
	return true;
}

bool WorkSpace::saveFile(const QByteArray &fileFormat)
{
	QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

	QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
		initialPath,
		tr("%1 Files (*.%2);;All Files (*)")
		.arg(QString(fileFormat.toUpper()))
		.arg(QString(fileFormat)));
	if (fileName.isEmpty()) {
		return false;
	} else {
		return scribbleboard->saveImage(fileName, fileFormat);
	}
}


/**********************Mesh Viewer***********************/

void WorkSpace::showNumViewers( int n )
{
	int count = 0, activeCount = 0;

	for(int i = 0; i < countX; i++){
		for(int j = 0; j < countY; j++){
			if(count++ < n)
			{
				viewers[i][j]->isActive = true;
				viewers[i][j]->clearMesh();
				viewers[i][j]->resetView();

				activeCount++;
			}
			else
				viewers[i][j]->isActive = false;
		}
	}

	refresh();

	numActiveViewers = activeCount;
}

void WorkSpace::loadMeshes(QString using_path)
{
	shapePath = using_path;

	// Get list of files
	QStringList filters;
	filters << "*.obj" << "*.off";
	files = QDir(shapePath).entryList(filters);

	int numPages = ceil(double(files.size()) / double(countX * countY)) - 1;

	ui.scrollBar_2->setRange(0, numPages);
	ui.scrollBar_2->setValue(0);

	if(files.size())
		loadMeshes();
	else
	{
		showNumViewers(0);
		refresh();
	}
}

void WorkSpace::loadMeshes()
{
	loadCurrentMeshes();
}

void WorkSpace::refresh()
{
	for(int i = 0; i < countX; i++)
		for(int j = 0; j < countY; j++)
			viewers[i][j]->updateGL();
}

void WorkSpace::loadCurrentMeshes()
{
	int numViewers = countX * countY;
	int index = ui.scrollBar_2->value() * numViewers;
	int curActive = Min(numViewers, files.size() - index);

	showNumViewers(curActive);

	int c = 0;

	for(int i = 0; i < countX; i++){
		for(int j = 0; j < countY; j++)
		{
			viewers[i][j]->clearMesh();
			viewers[i][j]->resetView();
		}
	}

	for(int i = 0; i < countX; i++){
		for(int j = 0; j < countY; j++)
		{
			if(index + c > files.size() - 1) return;

			QString fileName = shapePath + "\\" + files[index + c];

			new LoaderThread(viewers[i][j], fileName);

			c++; if(c > curActive) return;
		}
	}
}

void WorkSpace::loadMeshes(QStringList& filelist)
{
	int numPages = ceil(double(filelist.size()) / double(countX * countY)) - 1;

	ui.scrollBar_2->setRange(0, numPages);
	ui.scrollBar_2->setValue(0);

	if(filelist.size())
		loadMeshes();
	else
	{
		showNumViewers(0);
		refresh();
	}
}

void WorkSpace::setActiveViewer( QuickMeshViewer* v)
{
	activeViewer = v;
}

QString WorkSpace::selectedFile()
{
	if(activeViewer) return activeViewer->meshFileName();
	return "";
}

void WorkSpace::showEvent( QShowEvent * event )
{
	activeViewer->setFocus();
}

/********************************Retrieval**************************************/

double WorkSpace::imgDistance(imgFile *img1, imgFile *img2)
{
	double dist = 0.0;
	double *fbank1 = new double[MAXLENGTH]; 
	fbank1 = extractFeatures(img1, gaborOpt, gistOpt, wght, flen); 
	double *fbank2 = new double[MAXLENGTH]; 
	fbank2 = extractFeatures(img2, gaborOpt, gistOpt, wght, flen);

	for(int i = 0; i < *flen; i++)
	{
		dist += (fbank1[i] - fbank2[i]) * (fbank1[i] - fbank2[i]);
	}

	delete []fbank1;
	delete []fbank2;
	return dist;
}

double WorkSpace::imgDistance(double *lhs, double *rhs)
{
	double dist = 0.0;

	for(int i = 0; i < *flen; i++)
	{
		dist += (lhs[i] - rhs[i]) * (lhs[i] - rhs[i]);
	}

	return dist;
}


void WorkSpace::rankResults()
{
	
	std::sort(dataset.begin(),dataset.end(), cmpfunc);
}

bool WorkSpace::isInlist(QVector<QString> &mlist, QString &ini)
{
	int mSize = mlist.size();
	for (int i = 0; i < mSize; i++)
	{
		if(ini == mlist[i])
			return true;
	}

	return false;
}

void WorkSpace::updateFileList()
{
	files.clear();
	QVector<QString> fnlist;
	int mSize = 0;
	if (dataset.size() > 20)
		mSize = 20;
	else
		mSize = dataset.size();

    QString curfile = dataset[0].initial + "\\" + dataset[0].initial + ".off";
	fnlist.push_back(dataset[0].initial);
	files<<dataset[0].initial + "\\" + dataset[0].initial + ".off";
	for (int i = 1; i < mSize; i++)
	{
		if (isInlist(fnlist, dataset[i].initial))
			continue;
		else{
			curfile = dataset[i].initial + "\\" + dataset[i].initial + ".off";
			files<<curfile;
			fnlist.push_back(dataset[i].initial);
		}	   
	}

	dataset = srcData;
}

void WorkSpace::get3Dfn(const QString& src, const QString& refChar,QString& res)
{
	int idx = src.lastIndexOf(refChar);
	res = src.left(idx);
}

bool WorkSpace::loadParam(const QString &mFile)
{
	std::ifstream inFile(mFile.toStdString().c_str());

	if(!inFile)
		return false;
	
	std::string vStr;
	std::vector<int> val; 
	bool ok;
	while(getline(inFile, vStr))
	{
		QString str(vStr.c_str());
	    val.push_back(str.toInt(&ok, 10));
	}

	for (int i = 0; i < 4; i++)
	{
		gaborOpt[i] = val[i];
		gistOpt[i] = val[4+i];
		wght[i] = val[8+i];
	}

	return true;
}

void WorkSpace::initEngine()
{
	shapePath = "D:\\Projects\\SktShpRetrieval\\ShapeRetr\\Data\\Shapes";
	imagePath = "D:\\Projects\\SktShpRetrieval\\ShapeRetr\\Data\\Images";
	
	CDataFile feaFile( FEATUREFILE,DF::RF_READ_AS_STRING|DF:: RF_READ_AS_DOUBLE);
	int nCol = feaFile.GetNumberOfSamples(1);
	int nVol = feaFile.GetNumberOfVariables();
	
	//Load all line renderings
	QStringList filters, filelist;
	//filters << "*.png";
	//filelist = QDir(imagePath).entryList(filters);
	filelist = QDir(imagePath).entryList();
	int mSize = filelist.size();
	
	/*assert(mSize == nCol);*/

	for (int i = 2; i < mSize; i++)
	{
	   int mlen = filelist[i].size();
	   QString fileName = imagePath + "\\" + filelist[i] + "\\" + filelist[i].right(mlen - 1) + ".png";
	   //QString mInit;
	   //get3Dfn(filelist[i], "_", mInit);
	   imgFile img;
	   img.id = i;
	   img.fname = fileName.toLatin1().data();
	   img.fname = new char[fileName.length()];
	   strcpy(img.fname, fileName.toStdString().c_str());
	   //RetrData curData(0.0, mInit,img);
	   RetrData curData(0.0, filelist[i], img, NULL);
	   srcData.push_back(curData);	

	   srcData[i-2].feaVec = new double[nVol-1];
	   for (int j = 0; j < nVol-1; j++)
	   {
		  srcData[i-2].feaVec[j] = feaFile.GetData(j,i-2);
	   }
	}

	dataset = srcData;

	//Init parameters
	if(!loadParam(CONFIGPATH))
	{
		QMessageBox msgBox;
		msgBox.setText("Fail to load configuration file.");
		msgBox.exec();

	}
	flen = Malloc( int, 1);
}

void WorkSpace::genofflineData()
{
	std::fstream fs;
	fs.open("D:\\Projects\\SktShpRetrieval\\ShapeRetr\\Data\\features.csv",std::ios::out|std::ios::app);
	int mSize = dataset.size();
	for(int i = 0; i< mSize; i++)
	{
		double *fbank = new double[728];
		fbank = extractFeatures(&dataset[i].img, gaborOpt, gistOpt, wght, flen);
		for (int j = 0; j < *flen; j++)
		{
			fs<<fbank[j]<<",";
		}
		fs<<std::endl;
		delete []fbank;
	}
	fs.close();
}

void WorkSpace::search()
{
	//Read sketch
	scribbleboard->saveImage("D:\\Projects\\SktShpRetrieval\\ShapeRetr\\Data\\tmp.png", "png");

	double *feaVec = new double[MAXLENGTH];
	feaVec = calFeature();
	
	int mSize = dataset.size();
	for (int i= 0; i < mSize; i++)
	{
		dataset[i].dist = imgDistance(feaVec, dataset[i].feaVec);
		//dataset[i].dist = imgDistance(curSketch, &dataset[i].img);
	}

	rankResults();

	updateFileList();

	loadMeshes(files);

}

double* WorkSpace::calFeature()
{
	//double *fbank = new double[MAXLENGTH];
	double *fbank = extractFeatures(curSketch, gaborOpt, gistOpt, wght, flen); 
	return fbank;
}

/***************************Thread control*****************************/
LoaderThread::LoaderThread(QuickMeshViewer * v, QString file_name)
{
	this->viewer = v;
	this->fileName = file_name;
	this->start();
}

void LoaderThread::run()
{
	this->viewer->loadMesh(fileName);
	QThread::exit();
}