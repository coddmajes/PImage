
// PImage.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "PImage.h"
#include "MainFrm.h"

#include "PImageDoc.h"
#include "LeftView.h"
#include "PImageView.h"
#include "SmoothDlg.h"
#include "PPieceGray.h"
#include "LogDlg.h"
#include "SharpenDlg.h"

#include "cv.h"
#include "highgui.h"
#include <math.h>

//#include "opencv.hpp"


using namespace std;
using namespace cv;

#define GRAY_LEVEL 255
#define REVERSE -1
#define LEFT 1
#define RIGHT 0


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPImageApp

BEGIN_MESSAGE_MAP(CPImageApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CPImageApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CPImageApp::OnFileOpen)
	//各类图像变换操作
	ON_COMMAND(ID_FOURIER_TRANSFORM, &CPImageApp::OnTransformChoiceF)
	ON_COMMAND(ID_FOURIER_REVERSER, &CPImageApp::OnTransformChoiceFR)
	ON_COMMAND(ID_DCT_TRANSFORM, &CPImageApp::OnTransformChoiceDCT)
	ON_COMMAND(ID_DCT_REVERSE, &CPImageApp::OnTransformChoiceDCTR)
	ON_COMMAND(ID_GLT_INVERSE, &CPImageApp::OnGltInverse)
	ON_COMMAND(ID_DSCRETCH, &CPImageApp::OnScretch)
	ON_BN_CLICKED(IDOK, &CPImageApp::OnBnClickedOk)
	ON_BN_CLICKED(2, &CPImageApp::OnBnClicked2)
	ON_COMMAND(ID_LAYER, &CPImageApp::OnLayer)
	ON_COMMAND(ID_BIT_LAYER, &CPImageApp::OnBitLayer)
	ON_COMMAND(ID_GLT_LOGARITHM, &CPImageApp::OnGltLogarithm)
	ON_COMMAND(ID_HISTOGRAM_GRAY, &CPImageApp::OnHistogramGray)
	ON_COMMAND(ID_HISTOGRAM_EQUALIZATION, &CPImageApp::OnHistogramEqualization)
	ON_COMMAND(ID_HISTOGRAM_REGULARIZATION, &CPImageApp::OnHistogramRegularization)
	//ON_COMMAND(ID_FILTER_SMOOTH, &CPImageApp::OnFilterSmooth)
	ON_COMMAND(ID_AVERAGE_FILTER, &CPImageApp::OnAverageFilter)
	ON_COMMAND(ID_MEDIAN_FILTER, &CPImageApp::OnMedianFilter)
	ON_COMMAND(ID_MAX_FILTER, &CPImageApp::OnMaxFilter)
	ON_COMMAND(ID_MIN, &CPImageApp::OnMin)
	ON_COMMAND(ID_LA_FILTER, &CPImageApp::OnLaFilter)
	ON_COMMAND(ID_LA_GRAY, &CPImageApp::OnLaGray)
	ON_COMMAND(ID_ROBERTS, &CPImageApp::OnRoberts)
	ON_COMMAND(ID_PREWITT, &CPImageApp::OnPrewitt)
	ON_COMMAND(ID_SOBEL, &CPImageApp::OnSobel)
	ON_COMMAND(ID_HORI_VERT, &CPImageApp::OnHoriVert)
	
	//ON_COMMAND(ID_POWER, &CPImageApp::OnPower)
	ON_COMMAND(ID_TEST, &CPImageApp::OnTest)
	
	
	ON_COMMAND(ID_ILPF, &CPImageApp::OnIlpf)
	
	ON_COMMAND(ID_BLPF, &CPImageApp::OnBlpf)
	ON_COMMAND(ID_BHPF, &CPImageApp::OnBhpf)
	ON_COMMAND(ID_GLPF, &CPImageApp::OnGlpf)
	ON_COMMAND(ID_GHPF, &CPImageApp::OnGhpf)
	ON_COMMAND(ID_IHPF, &CPImageApp::OnIhpf)
	ON_COMMAND(ID_LIGHT, &CPImageApp::OnLight)
	
END_MESSAGE_MAP()


// CPImageApp 构造

CPImageApp::CPImageApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则:
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("PImage.AppID.NoVersion"));
	m_drawon = true;//设置绘图状态为true
	m_last_recoverNum = 0;
	//m_facecut = false;//默认不进行人脸识别
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}
CPImageApp::~CPImageApp()
{
	m_image.Destroy();
}
// 唯一的一个 CPImageApp 对象

CPImageApp theApp;


// CPImageApp 初始化

BOOL CPImageApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)


	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CPImageDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CLeftView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	m_pMainWnd->SetWindowText("181120083_数媒_周筝");
	return TRUE;
}

int CPImageApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}


void CPImageApp::OnFileOpen()
{
	CString filePath;
	char szFilter[] = {"图片文件（*.bmp;*.jpg;*.gif;*.tif;*.png;*.jpeg;*.psd;*.dng）|*.bmp;*.jpg;*.gif;*.tif;*.png;*.jpeg;*.psd;*.dng||"};
	
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
	if(dlg.DoModal())
	{
		m_openFilePath = dlg.GetPathName();
		CString lena_guidinghua = dlg.GetFileName();
		if(lena_guidinghua == "lena_guidinghua.png")
		{
			m_guidinghuaPath = m_openFilePath;
		}
		//CMainFrame* mf = (CMainFrame*)AfxGetMainWnd();
		//CLeftView* left = dynamic_cast<CLeftView*>(mf->GetActiveView());
		
		/*
		CLeftView *left;
		CREATESTRUCT cs;
		left->PreCreateWindow(cs);*/
		
		CMainFrame* mf = (CMainFrame*)AfxGetMainWnd();
		//mf->GetLeftPane();
		if (mf->GetLeftPane()) {
			if(!m_image.IsNull())
			{
				m_image.Destroy();
			}
			m_image.Load(m_openFilePath);
			mf->GetLeftPane()->setImage(m_image);
			//mf->GetLeftPane()->OnOpenLeftImage(m_openFilePath);
		}
		mf->GetLeftPane()->Invalidate(TRUE);
	}
}
// CPImageApp 消息处理程序


class Histogram1D
{
private:
    int histSize[1]; // 项的数量
    float hranges[2]; // 统计像素的最大值和最小值
    const float* ranges[1];
    int channels[1]; // 仅计算一个通道

	int m_choice;
	int m_inten[256];//
	

public:
    Histogram1D()
    {
        // 准备1D直方图的参数
        histSize[0] = 256;
        hranges[0] = 0.0f;
        hranges[1] = 255.0f;
        ranges[0] = hranges;
        channels[0] = 0;
    }
	
    Mat getHistogram(const Mat &image)
    {
        Mat hist;
        // 计算直方图
        calcHist(&image ,// 要计算图像的
            1,                // 只计算一幅图像的直方图
            channels,        // 通道数量
            Mat(),            // 不使用掩码
            hist,            // 存放直方图
            1,                // 1D直方图
            histSize,        // 统计的灰度的个数
            ranges);        // 灰度值的范围
        return hist;
    }

	enum { IDM_THRESHOLD = ID_THRESHOLD, //阈值处理
		IDM_GLOBAL_THRESHOLD = ID_GLOBAL_THRESHOLD,//基本全局阈值处理
		IDM_OTSU_THRESHOLD = ID_OTSU_THRESHOLD,//OTSU的最佳阈值处理

	};

    Mat getHistogramImage(const Mat &image,int choice)
    {
		m_choice = choice;
        Mat hist = getHistogram(image);
        //查找最大值用于归一化
        double maxVal = 0;

        minMaxLoc(hist, NULL, &maxVal);

        //绘制直方图的图像
        Mat histImg(histSize[0], histSize[0], CV_8U, Scalar(255));//scalar对通道中每个像素都赋值255

        // 设置最高点为最大值的90%
        //double hpt = 0.9 * histSize[0];
		double hpt = histSize[0];
        //每个条目绘制一条垂直线
		int sum =0;
		
        for (int h = 0; h < histSize[0]; h++)
        {
            //直方图的元素类型为32位浮点数
            float binVal = hist.at<float>(h);
            int intensity = static_cast<int>(binVal * hpt / maxVal);
			//int intensity = static_cast<int>(binVal  / maxVal);
            line(histImg, Point(h, histSize[0]),
                    Point(h, histSize[0] - intensity), Scalar::all(0));//坐标起点在左上角
			sum += intensity;
			m_inten[h] = intensity;
			
        }
		if(m_choice == IDM_GLOBAL_THRESHOLD || m_choice == IDM_OTSU_THRESHOLD)
		{
			theApp.getHis(sum,m_inten);
		}
        return histImg;
    }
};

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CPImageApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void CPImageApp::OnMenu()
{
	m_recover = false;
	if(!m_drawon)
	{
		return;
	}

	switch(m_choice)
	{
		case IDM_F:
			OnFourierTransform(IDM_F);
			break;
		case IDM_FR:
			OnFourierTransform(IDM_FR);
			break;
		case IDM_DCT:
			OnDCTTransform(IDM_DCT);
			break;
		case IDM_DCTR:
			OnDCTTransform(IDM_DCTR);
			break;
		case IDM_GLT_INVERSE:
			OnAnticolorChange();//反色处理
			break;
		case ID_DSCRETCH:
			OnPiecewiseLinearTransform();//对比度拉伸
			break;
		case ID_LAYER:
			OnPiecewiseLinearTransform();//灰度级变换
			break;
		case ID_BIT_LAYER:
			OnPiecewiseLinearTransform();
			break;
		case IDM_GLT_LOGARITHM:
			OnLogTransform();//对数变换
			break;
			/*
		case IDM_POWER:
			OnPowerShow();//幂次变换
			break;
			*/
		case IDM_HISTOGRAM_GRAY:
			OnHistogramGrayShow();//显示直方图
			break;
		case IDM_HISTOGRAM_EQUALIZATION:
			OnHistogramGrayShow();//直方图均衡化
			break;
		case IDM_HISTOGRAM_REGULARIZATION:
			OnHistogramRegularizationShow();//直方图规定化
			break;
	/*	case IDM_FILTER_SMOOTH:
			OnFilterSmoothShow();//空域平滑处理
			break;*/
		case IDM_AVERAGE_FILTER:
			OnAverageFilterShow();//空域均值滤波
			break;
		case IDM_MEDIAN_FILTER:
			OnMedianFilterShow();//空域中值滤波
			break;
		case IDM_MAX_FILTER:
			OnMaxFilterShow();//空域最大值滤波
			break;
		case IDM_MIN:
			OnMaxFilterShow();//空域最大值滤波
			break;
			
		case IDM_LA_FILTER:
			OnLaFilterShow();//空域锐化 拉普拉斯算子
			break;
		case IDM_LA_GRAY:
			OnLaFilterShow();//空域锐化 拉普拉斯算子 加原图
			break;
			
		case IDM_HORI_VERT:
			OnRobertsShow();//空域锐化 水平垂直算子
			break;
		case IDM_ROBERTS:
			OnRobertsShow();//空域锐化 roberts算子
			break;
		case IDM_PREWITT:
			OnPrewittShow();//空域锐化 prewitt算子
			break;
		case IDM_SOBEL:
			OnPrewittShow();//空域锐化 sobel算子
			break;
		case IDM_ILPF:
			OnIlpfShow();//频域理想低通滤波器 
			break;
		case IDM_IHPF:
			OnIlpfShow();//频域理想高通滤波器 
			break;
		case IDM_BLPF:
			OnBlpfShow();//频域巴特沃斯低通滤波器
			break;
		case IDM_BHPF:
			OnBlpfShow();//频域巴特沃斯高通滤波器
			break;
		case IDM_GLPF:
			OnGlpfShow();////高斯低通滤波
			break;
		case IDM_GHPF:
			OnGlpfShow();//高斯高通滤波
			break;
		case IDM_LIGHT:
			OnLightShow();//加亮点
			break;
			
	}
}

void CPImageApp::OnTransformChoiceF()
{
	m_choice = IDM_F;
	OnMenu();
	
}
void CPImageApp::OnTransformChoiceFR()
{
	m_choice = IDM_FR;
	OnMenu();
	
}
void CPImageApp::OnTransformChoiceDCT()
{
	m_choice = IDM_DCT;
	OnMenu();
	
}
void CPImageApp::OnTransformChoiceDCTR()
{
	m_choice = IDM_DCTR;
	OnMenu();
	
}
void CPImageApp::OnGltInverse()//反色处理
{
	m_choice = IDM_GLT_INVERSE;
	OnMenu();
	
}

void CPImageApp::OnScretch()//对比度拉伸
{
	m_choice = ID_DSCRETCH;
	PPieceGray dlg;
	dlg.setDlgTitle("对比度拉伸");
	dlg.DoModal();
	OnMenu();
}

void CPImageApp::OnLayer()//灰度级分层
{
	m_choice = ID_LAYER;
	OnMenu();
}

void CPImageApp::OnBitLayer()//比特层面分层
{
	m_choice = ID_BIT_LAYER;
	OnMenu();
}

void CPImageApp::MatToCImage(Mat& mat, CImage& cimage)
{
	
	int width = mat.cols;
	int height = mat.rows;
	int channels = mat.channels();
	uchar * s = mat.data;
	cimage.Destroy();//这一步是防止重复利用造成内存问题
	cimage.Create(width,height,8*channels);
	
	uchar* ps;
	uchar* pimg = (uchar*)cimage.GetBits(); //获取CImage的像素存贮区的指针
	int step = cimage.GetPitch();//每行的字节数,注意这个返回值有正有负
	
	// 如果是1个通道的图像(灰度图像) DIB格式才需要对调色板设置  
	// CImage中内置了调色板，我们要对他进行赋值：
	
	if (1 == channels)
	{
		RGBQUAD* ColorTable;  
		int MaxColors=256;  
		//cimage.GetMaxColorTableEntries();//返回调色板单元数
		//这里可以通过CI.GetMaxColorTableEntries()得到大小(如果你是CI.Load读入图像的话)  
		ColorTable = new RGBQUAD[MaxColors];  
		cimage.GetColorTable(0,MaxColors,ColorTable);//这里是取得指针  
		for (int i=0; i<MaxColors; i++)  
		{  
			ColorTable[i].rgbBlue = (uchar)i;  
			//BYTE和uchar一回事，但MFC中都用它  
			ColorTable[i].rgbGreen = (uchar)i;  
			ColorTable[i].rgbRed = (uchar)i;  
		}  
		cimage.SetColorTable(0,MaxColors,ColorTable);  
		delete []ColorTable;  
	}
			int cout =0;
	for (int i = 0; i < height; i++)
	{
		ps = (mat.ptr<uchar>(i));//向mat第i行第一个元素的指针
		//ps = (mat.at<uchar*>(i));//向mat第i行第一个元素的指针
		for (int j = 0; j < width; j++)
		{
			for(int nCha = 0 ; nCha < channels; nCha++)
			{
				*(pimg +i*step+ j*channels + nCha) = ps[j*channels + nCha];
			}
		}
	}
	
}

void CPImageApp::CImageToMat(CImage& cimage, Mat& mat)
{
	if (true == cimage.IsNull())
	{
		return;
	}
	int nWidth    = cimage.GetWidth();
	int nHeight   = cimage.GetHeight();
	int nChannels = cimage.GetBPP() / 8;
	Mat imat;
	//重建mat
	if (1 == nChannels)
	{
		mat.create(nHeight, nWidth, CV_8UC1);
	}
	else if(3 == nChannels)
	{
		mat.create(nHeight, nWidth, CV_8UC3);
	}
	else
	{
		mat.create(nHeight, nWidth, CV_8UC3);
	}
	//拷贝数据
	uchar* pucRow;									//指向数据区的行指针
	uchar* pucImage = (uchar*)cimage.GetBits();		//指向数据区的指针
	int nStep = cimage.GetPitch();					//每行的字节数,注意这个返回值有正有负
	int channels = mat.channels();
 
	for (int nRow = 0; nRow < nHeight; nRow++)
	{
		pucRow = (mat.ptr<uchar>(nRow));
		for (int nCol = 0; nCol < nWidth; nCol++)
		{
			for (int nCha = 0 ; nCha < channels; nCha++)
			{
				pucRow[nCol *channels + nCha] = *(pucImage + nRow * nStep + nCol *channels + nCha);
			}
		}	
	}
}
Mat CPImageApp::ReadImage()
{
	if(!m_image.IsNull())
	{
		m_image.Destroy();
	}
	m_image.Load(m_openFilePath);
	if(m_image.IsNull())
	{
		cout<<"error";
	}
	Mat imat;
	CImageToMat(m_image,imat);
	return imat;
}

void CPImageApp::ShowImage(Mat& mat)
{
	CMainFrame* mf = (CMainFrame*)AfxGetMainWnd();
	CPImageView *cimageview = mf->GetRightPane();
	if(!m_image.IsNull())
	{
		m_image.Destroy();
	}
	if(!m_img->IsNull())
	{
		for(int i=0;i<m_last_recoverNum;i++)
		{
			m_img[i].Destroy();
		}
		
	}
	if (cimageview) 
	{
		if(m_recover)
		{
			for(int i =0; i<m_recoverNum; i++)
			{
				MatToCImage(m_mat[i],m_img[i]);
			}
			m_last_recoverNum = m_recoverNum;
			cimageview->setImg(m_img,m_choice);
		}
		else
		{
			MatToCImage(mat,m_image);
			cimageview->setImage(m_image,m_choice);
			
		}

		//delete []m_mat;
		cimageview->Invalidate(TRUE);
		//cimageview->DisplayImage(cimageview,m_image );
		//m_image.Destroy();
	}
	

}

void  CPImageApp::RGBtoGRAY(Mat& mat, Mat& gray)
{
	int chanels = mat.channels();
	if(chanels != 1)
	{
		cvtColor(mat,gray,CV_RGB2GRAY);  
	}
	else
	{
		 gray = mat.clone();
	}
}

void  CPImageApp::saltAndPeper(Mat&image,int phi = 256)
{
    int hight = image.rows;
    int width = image.cols;
    srand((unsigned)time((0)));
    for (int i = 0; i < phi; i++)
    {
        int x = rand() % hight;
        int y = rand() % width;
        image.at<uchar>(x, y) = rand() % 255;
        //image.at<cv::Vec3b>(x, y)[1] = rand() % 255;
        //image.at<cv::Vec3b>(x, y)[2] = rand() % 255;
    }
}

void CPImageApp::getMatrix(int modelMatrix)
{
	m_modelMatrix = modelMatrix;
}

void CPImageApp::getDefault(bool default)
{
	m_default = default;
}

void CPImageApp::getSharpenText(int* text, int choice,int patern_num)
{
	if(patern_num == SINGLE_LEFT)
	{
		if(m_leftText!=nullptr)
		{
			//delete m_text;
			m_leftText = nullptr;
		}
	}
	else if (patern_num == SINGLE_RIGHT)
	{
		if( m_rightText != nullptr)
		{
			m_rightText = nullptr;
		}
	}
	else if (patern_num == DOUBLE_PATREN)
	{
		if(m_leftText!=nullptr && m_rightText != nullptr)
		{
			m_leftText = nullptr;
			m_rightText = nullptr;
		}
	}
	m_defalt_singlepatern = patern_num;
	if(choice == LEFT)
	{
		m_leftText = text;
	}
	else if(choice == RIGHT)
	{
		m_rightText = text;
	}
	
}
void CPImageApp::setDrawonStatu(bool statu)
{
	m_drawon = statu;
}

void CPImageApp::getText(float* text)
{
	if(m_text!=nullptr)
	{
		//delete m_text;
		m_text = nullptr;
		
	}
	m_text = text;
}

Mat CPImageApp::OnFFT(Mat mat)
{
	Mat imat = mat.clone();
	int m = getOptimalDFTSize(imat.rows);
	int n = getOptimalDFTSize(imat.cols);
	Mat gray_img = mat.clone();
	Mat padded;                 //以0填充输入图像矩阵

    //填充输入图像imat，输入矩阵为padded，上方和左方不做填充处理
    copyMakeBorder(gray_img, padded, 0, m - gray_img.rows, 0, n - gray_img.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(),CV_32F) };
    Mat complexI;
    merge(planes, 2, complexI);     //将planes融合合并成一个多通道数组complexI
	dft(complexI, complexI);        //进行傅里叶变换
	split(complexI, planes);        //planes[0] = Re(DFT(I),planes[1] = Im(DFT(I))
                                  //即planes[0]为实部,planes[1]为虚部
    magnitude(planes[0], planes[1], planes[0]);     //planes[0] = magnitude
    Mat magI = planes[0];
    magI += Scalar::all(1);
    log(magI, magI);                //转换到对数尺度(logarithmic scale)

    //如果有奇数行或列，则对频谱进行裁剪
    magI = magI(Rect(0, 0, magI.cols&-2, magI.rows&-2));
    //重新排列傅里叶图像中的象限，使得原点位于图像中心
    int cx = magI.cols / 2;
    int cy = magI.rows / 2;

    Mat q0(magI, Rect(0, 0, cx, cy));       //左上角图像划定ROI区域
    Mat q1(magI, Rect(cx, 0, cx, cy));      //右上角图像
    Mat q2(magI, Rect(0, cy, cx, cy));      //左下角图像
    Mat q3(magI, Rect(cx, cy, cx, cy));     //右下角图像

    //变换左上角和右下角象限
    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    //变换右上角和左下角象限
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
	
	planes[0]+=Scalar::all(1);//傅立叶变换后的图片不好分析，进行对数处理，结果比较好看
	log(planes[0],planes[0]);
    //归一化处理，用0-1之间的浮点数将矩阵变换为可视的图像格式
    normalize(magI, magI, 0, 1, CV_MINMAX);
	magI.convertTo(magI, CV_8UC1, 255, 0);
	return magI;
	//ShowImage(magI);
}

void CPImageApp::getHis(int sum, int * intensity)
{
	m_hsum = sum;
	m_intensity = intensity;
}



void CPImageApp::OnLightShow()//加亮点
{
	m_recover = true;
	Mat imat = ReadImage();
	// 输入图像判断
    if (imat.empty())
        return;
	int chanels = imat.channels();
	Mat gray_img,dstMat;
	RGBtoGRAY(imat,gray_img);//RGB转换GRAY
	dstMat = gray_img.clone();
	int nRows = dstMat.rows;
	int nCols = dstMat.cols;
	int pos_x = 210, pos_y = 160;
	for (int i = 0; i < nRows - 1; i++){
		for (int j = 0; j < nCols - 1; j++){
			if(i == pos_x && j == pos_y)
			{
				dstMat.at<uchar>(i, j) = 255;//打亮点
			}
		}
	}
	//imshow("33",dstMat);
	if(m_choice == IDM_LIGHT)
	{
		m_mat[0] = dstMat;
		m_recoverNum = 1;
		ShowImage(dstMat);//加亮点
	}
	

	
	
}


Mat CPImageApp::freqfilt(Mat &padded,Mat &butterworth_pass)
{
	//***********************DFT*******************
	Mat plane[]={padded, Mat::zeros(padded.size() , CV_32FC1)}; //创建通道，存储dft后的实部与虚部（CV_32F，必须为单通道数）
	Mat complexIm;
	merge(plane,2,complexIm);//合并通道 （把两个矩阵合并为一个2通道的Mat类容器）
	dft(complexIm,complexIm);//进行傅立叶变换，结果保存在自身

	//***************中心化********************
	split(complexIm,plane);//分离通道（数组分离）
	//    plane[0] = plane[0](Rect(0, 0, plane[0].cols & -2, plane[0].rows & -2));//这里为什么&上-2具体查看opencv文档
	//    //其实是为了把行和列变成偶数 -2的二进制是11111111.......10 最后一位是0
	int cx=plane[0].cols/2;int cy=plane[0].rows/2;//以下的操作是移动图像  (零频移到中心)
	Mat part1_r(plane[0],Rect(0,0,cx,cy)); //元素坐标表示为(cx,cy)
	Mat part2_r(plane[0],Rect(cx,0,cx,cy));
	Mat part3_r(plane[0],Rect(0,cy,cx,cy));
	Mat part4_r(plane[0],Rect(cx,cy,cx,cy));

	Mat temp;
	part1_r.copyTo(temp);	//左上与右下交换位置(实部)
	part4_r.copyTo(part1_r);
	temp.copyTo(part4_r);

	part2_r.copyTo(temp);	//右上与左下交换位置(实部)
	part3_r.copyTo(part2_r);
	temp.copyTo(part3_r);

	Mat part1_i(plane[1],Rect(0,0,cx,cy));	//元素坐标(cx,cy)
	Mat part2_i(plane[1],Rect(cx,0,cx,cy));
	Mat part3_i(plane[1],Rect(0,cy,cx,cy));
	Mat part4_i(plane[1],Rect(cx,cy,cx,cy));

	part1_i.copyTo(temp);	//左上与右下交换位置(虚部)
	part4_i.copyTo(part1_i);
	temp.copyTo(part4_i);

	part2_i.copyTo(temp);	//右上与左下交换位置(虚部)
	part3_i.copyTo(part2_i);
	temp.copyTo(part3_i);

	//*****************滤波器函数与DFT结果的乘积****************
	Mat blur_r,blur_i,BLUR;
	multiply(plane[0], butterworth_pass, blur_r); //滤波（实部与滤波器模板对应元素相乘）
	multiply(plane[1], butterworth_pass,blur_i);//滤波（虚部与滤波器模板对应元素相乘）
	Mat plane1[]={blur_r, blur_i};
	merge(plane1,2,BLUR);//实部与虚部合并

	//*********************得到原图频谱图***********************************
	magnitude(plane[0],plane[1],plane[0]);//获取幅度图像，0通道为实部通道，1为虚部，因为二维傅立叶变换结果是复数
	plane[0]+=Scalar::all(1);	//傅立叶变换后的图片不好分析，进行对数处理，结果比较好看
	log(plane[0],plane[0]);		// float型的灰度空间为[0，1])
	//归一化处理，用0-1之间的浮点数将矩阵变换为可视的图像格式
   // normalize(magI, magI, 0, 1, CV_MINMAX);
	normalize(plane[0],plane[0],0,1,CV_MINMAX);	//归一化便于显示
	plane[0].convertTo(plane[0], CV_8UC1, 255, 0);

	idft( BLUR, BLUR);	//idft结果也为复数
	split(BLUR,plane);//分离通道，主要获取通道
	magnitude(plane[0],plane[1],plane[0]);	//求幅值(模)
	normalize(plane[0],plane[0],1,0,CV_MINMAX);	//归一化便于显示
	plane[0].convertTo(plane[0], CV_8UC1, 255, 0);
	return plane[0];
}


void CPImageApp::OnGlpfShow()//高斯低通滤波
{
	Mat imat = ReadImage();
	// 输入图像判断
    if (imat.empty())
        return;
	int chanels = imat.channels();
	Mat gray_img,dstMat;
	RGBtoGRAY(imat,gray_img);//RGB转换GRAY
	//dstMat = gray_img.clone();
	int nRows = dstMat.rows;
	int nCols = dstMat.cols;

	//调整图像加速傅里叶变换
	int M = getOptimalDFTSize(gray_img.rows);
	int N = getOptimalDFTSize(gray_img.cols);
	Mat padded;
	copyMakeBorder(gray_img, padded, 0, M - gray_img.rows, 0, N - gray_img.cols, BORDER_CONSTANT, Scalar::all(0));
	padded.convertTo(padded,CV_32FC1); //将图像转换为flaot型

	Mat gaussianBlur(padded.size(),CV_32FC1); //，CV_32FC1
	int n = theApp.m_text[0], sigma = theApp.m_text[1];
	float d0=2*sigma*sigma;//高斯函数参数，越小，频率高斯滤波器越窄，滤除高频成分越多，图像就越平滑
	for(int i=0;i<padded.rows ; i++ ){
		for(int j=0; j<padded.cols ; j++ ){
			float d=pow(float(i-padded.rows/2),2)+pow(float(j-padded.cols/2),2);//分子,计算pow必须为float型
			if(m_choice == IDM_GLPF)//高斯低通滤波
			{
				gaussianBlur.at<float>(i,j)=expf(-d/d0);//expf为以e为底求幂（必须为float型）
			}
			else if(m_choice == IDM_GHPF)////高斯高通滤波
			{
				gaussianBlur.at<float>(i,j)=1-expf(-d/d0);//expf为以e为底求幂（必须为float型）
			}
		}
	}
	if(m_choice == IDM_GLPF)//高斯低通滤波
	{
		imshow("高斯低通滤波器",gaussianBlur);
	}
	else if(m_choice == IDM_GHPF)////高斯高通滤波
	{
		imshow("高斯高通滤波器",gaussianBlur);
	}
	
	dstMat = freqfilt(padded,gaussianBlur);
	dstMat(cv::Rect(0,0, gray_img.cols, gray_img.rows));

	ShowImage(dstMat);
}
/*
void CPImageApp::OnBhpfShow()//频域巴特沃斯高通滤波器
{
	Mat imat = ReadImage();
	// 输入图像判断
    if (imat.empty())
        return;
	int chanels = imat.channels();
	Mat gray_img,dstMat;
	RGBtoGRAY(imat,gray_img);//RGB转换GRAY
	//dstMat = gray_img.clone();
	int nRows = dstMat.rows;
	int nCols = dstMat.cols;

	//H = 1 / (1+(D/D0)^2n)    n表示巴特沃斯滤波器的次数

	//调整图像加速傅里叶变换
	int M = getOptimalDFTSize(gray_img.rows);
	int N = getOptimalDFTSize(gray_img.cols);
	Mat padded;
	copyMakeBorder(gray_img, padded, 0, M - gray_img.rows, 0, N - gray_img.cols, BORDER_CONSTANT, Scalar::all(0));
	padded.convertTo(padded,CV_32FC1); //将图像转换为flaot型


	//    阶数n=1 无振铃和负值
	//    阶数n=2 轻微振铃和负值
	//    阶数n=5 明显振铃和负值
	//    阶数n=20 与ILPF相似
	Mat butterworth_high_pass(padded.size(),CV_32FC1); //，CV_32FC1
	int n = theApp.m_text[0], sigma = theApp.m_text[1];
	double D0 = sigma;//半径D0越小，模糊越大；半径D0越大，模糊越小
	for(int i=0;i<padded.rows ; i++ ){
		for(int j=0; j<padded.cols ; j++ ){
			double d = sqrt(pow((i - padded.rows/2),2) + pow((j - padded.cols/2),2));//分子,计算pow必须为float型
			butterworth_high_pass.at<float>(i,j)=1.0 / (1 + pow(D0 / d, 2 * n));
		}
	}
	string name = "布特沃斯高通滤波器d0=" + std::to_string(sigma) + "n=" + std::to_string(n);
	imshow(name, butterworth_high_pass);

	dstMat = freqfilt(padded,butterworth_high_pass);
	dstMat(cv::Rect(0,0, gray_img.cols, gray_img.rows));

	ShowImage(dstMat);

}
*/

void CPImageApp::OnBlpfShow()//频域巴特沃斯低通滤波器
{
	Mat imat = ReadImage();
	// 输入图像判断
    if (imat.empty())
        return;
	int chanels = imat.channels();
	Mat gray_img,dstMat;
	RGBtoGRAY(imat,gray_img);//RGB转换GRAY
	//dstMat = gray_img.clone();
	int nRows = dstMat.rows;
	int nCols = dstMat.cols;

	//H = 1 / (1+(D/D0)^2n)    n表示巴特沃斯滤波器的次数

	//调整图像加速傅里叶变换
	int M = getOptimalDFTSize(gray_img.rows);
	int N = getOptimalDFTSize(gray_img.cols);
	Mat padded;
	copyMakeBorder(gray_img, padded, 0, M - gray_img.rows, 0, N - gray_img.cols, BORDER_CONSTANT, Scalar::all(0));
	padded.convertTo(padded,CV_32FC1); //将图像转换为flaot型


	//    阶数n=1 无振铃和负值
	//    阶数n=2 轻微振铃和负值
	//    阶数n=5 明显振铃和负值
	//    阶数n=20 与ILPF相似
	Mat butterworth_low_pass(padded.size(),CV_32FC1); //，CV_32FC1
	int n = theApp.m_text[0], sigma = theApp.m_text[1];
	double D0 = sigma;//半径D0越小，模糊越大；半径D0越大，模糊越小
	for(int i=0;i<padded.rows ; i++ ){
		for(int j=0; j<padded.cols ; j++ ){
			double d = sqrt(pow((i - padded.rows/2),2) + pow((j - padded.cols/2),2));//分子,计算pow必须为float型
			
			if(m_choice == IDM_BLPF)//频域巴特沃斯低通滤波器
			{
				butterworth_low_pass.at<float>(i,j)=1.0 / (1 + pow(d / D0, 2 * n));
			}
			else if (m_choice == IDM_BHPF)//频域巴特沃斯高通滤波器
			{
				butterworth_low_pass.at<float>(i,j)=1.0 / (1 + pow(D0 / d, 2 * n));
			}
			
		}
	}
	string name;
	if(m_choice == IDM_BLPF)//频域巴特沃斯低通滤波器
	{
		name = "布特沃斯低通滤波器d0=" + std::to_string(sigma) + "n=" + std::to_string(n);
	}
	else if (m_choice == IDM_BHPF)//频域巴特沃斯高通滤波器
	{
		name = "布特沃斯高通滤波器d0=" + std::to_string(sigma) + "n=" + std::to_string(n);
	}
	imshow(name, butterworth_low_pass);

	dstMat = freqfilt(padded,butterworth_low_pass);
	dstMat(cv::Rect(0,0, gray_img.cols, gray_img.rows));

	ShowImage(dstMat);

}

void CPImageApp::OnIlpfShow()//频域理想低通滤波器
{
	Mat imat = ReadImage();
	// 输入图像判断
    if (imat.empty())
        return;
	int chanels = imat.channels();
	Mat gray_img,dstMat;
	RGBtoGRAY(imat,gray_img);//RGB转换GRAY

	//调整图像加速傅里叶变换
	int M = getOptimalDFTSize(gray_img.rows);
	int N = getOptimalDFTSize(gray_img.cols);
	Mat padded;
	copyMakeBorder(gray_img, padded, 0, M - gray_img.rows, 0, N - gray_img.cols, BORDER_CONSTANT, Scalar::all(0));
	padded.convertTo(padded,CV_32FC1); //将图像转换为flaot型 

	Mat ideal_low_pass(padded.size(),CV_32FC1); //，CV_32FC1
	int n = theApp.m_text[0], sigma = theApp.m_text[1];
	float d0=sigma;//半径D0越小，模糊越大；半径D0越大，模糊越小
	for(int i=0;i<padded.rows ; i++ ){
		for(int j=0; j<padded.cols ; j++ ){
			double d = sqrt(pow((i - padded.rows/2),2) + pow((j - padded.cols/2),2));//分子,计算pow必须为float型
			if(m_choice == IDM_ILPF)//理想低通滤波器
			{
				if (d <= d0){
					ideal_low_pass.at<float>(i,j)=1;
				}else{
					ideal_low_pass.at<float>(i,j)=0;
				}
			}
			else if (m_choice == IDM_IHPF)//频域理想高通滤波器
			{
				if (d <= d0){
					ideal_low_pass.at<float>(i,j)=0;
				}else{
					ideal_low_pass.at<float>(i,j)=1;
				}
			}
			
		}
	}
	string name;
	if(m_choice == IDM_ILPF)//理想低通滤波器
	{
		name = "理想低通滤波器d0=" + std::to_string(sigma);
	}
	else if (m_choice == IDM_IHPF)//频域理想高通滤波器
	{
		name = "理想高通滤波器d0=" + std::to_string(sigma);
	}
	imshow(name, ideal_low_pass);
	
	dstMat = freqfilt(padded,ideal_low_pass);
	dstMat(cv::Rect(0,0, gray_img.cols, gray_img.rows));

	ShowImage(dstMat);
}

/*
void CPImageApp::OnSobelShow()//空域锐化 sobel算子
{
	Mat imat = ReadImage();
	// 输入图像判断
    if (imat.empty())
        return;
	int ddepth = CV_16S;//防止输出图像深度溢出
	int scale = 1;//默认值  
	int delta = 0;//默认值 
	Mat src_blur,gray_img,dstMat;
	//高斯模糊  
	GaussianBlur( imat, src_blur, Size(3,3), 0, 0, BORDER_DEFAULT );
	int chanels = src_blur.channels();
	RGBtoGRAY(imat,gray_img);//RGB转换GRAY
	//生成 grad_x and grad_y  
	Mat grad_x, grad_y;  
	Mat abs_grad_x, abs_grad_y;   
	// Gradient X x方向梯度 1,0：x方向计算微分即导数  
	//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );  
	Sobel( gray_img, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );  
	convertScaleAbs( grad_x, abs_grad_x );  
	// Gradient Y y方向梯度 0，1：y方向计算微分即导数  
	//Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );  
	Sobel( gray_img, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );  
	convertScaleAbs( grad_y, abs_grad_y );  
  
	//近似总的梯度  
	addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dstMat );
	ShowImage(dstMat);
}
*/





void CPImageApp::OnPrewittShow()//空域锐化 prewitt算子
{
	Mat imat = ReadImage();
	// 输入图像判断
    if (imat.empty())
        return;
	int chanels = imat.channels();
	Mat gray_img,dstMat;
	RGBtoGRAY(imat,gray_img);//RGB转换GRAY
	dstMat = gray_img.clone();
	
	int nRows = dstMat.rows;
	int nCols = dstMat.cols;
	int x1,x2;
	for (int i = 0; i < nRows - 1; i++){
		for (int j = 0; j < nCols - 1; j++){
			//根据公式计算
			int pixl_gray = 0;
			if(m_choice == IDM_PREWITT || m_choice ==IDM_SOBEL )//Roberts算子
			{
				int edge1 = i-1, edge2 = j-1, edge3 = i+1, edge4 = j+1;
				if(edge1< 0 || edge2< 0 || edge3 >nRows - 1 || edge4 > nCols - 1)
				{
					continue;
				}
				
				
				if(m_defalt_singlepatern == SINGLE_LEFT)
				{
					int p1 = gray_img.at<uchar>(i-1, j-1)*theApp.m_leftText[0] + theApp.m_leftText[1] *gray_img.at<uchar>(i-1, j)
						+ theApp.m_leftText[2] *gray_img.at<uchar>(i-1, j + 1)
						+ gray_img.at<uchar>(i+1, j-1)*theApp.m_leftText[6] + theApp.m_leftText[7] *gray_img.at<uchar>(i+1, j)
						+ theApp.m_leftText[8] *gray_img.at<uchar>(i+1, j + 1);
				
					x1 = p1;
					x2 = 0;
				}
				else if(m_defalt_singlepatern == SINGLE_RIGHT)
				{
					x1 = 0;
					int p2 = gray_img.at<uchar>(i-1, j-1)*theApp.m_rightText[0] + theApp.m_rightText[3] *gray_img.at<uchar>(i, j-1)
						+ theApp.m_rightText[6] *gray_img.at<uchar>(i+1, j - 1)
						+ gray_img.at<uchar>(i-1, j+1)*theApp.m_rightText[2] + theApp.m_rightText[5] *gray_img.at<uchar>(i, j + 1)
						+ theApp.m_rightText[8] *gray_img.at<uchar>(i+1, j + 1);
					x2 = p2;
				}
				else if(m_defalt_singlepatern == DOUBLE_PATREN)
				{
					x1 = gray_img.at<uchar>(i-1, j-1)*theApp.m_leftText[0] + theApp.m_leftText[1] *gray_img.at<uchar>(i-1, j)
						+ theApp.m_leftText[2] *gray_img.at<uchar>(i-1, j + 1)
						+ gray_img.at<uchar>(i+1, j-1)*theApp.m_leftText[6] + theApp.m_leftText[7] *gray_img.at<uchar>(i+1, j)
						+ theApp.m_leftText[8] *gray_img.at<uchar>(i+1, j + 1);;
					x2 = gray_img.at<uchar>(i-1, j-1)*theApp.m_rightText[0] + theApp.m_rightText[3] *gray_img.at<uchar>(i, j-1)
						+ theApp.m_rightText[6] *gray_img.at<uchar>(i+1, j - 1)
						+ gray_img.at<uchar>(i-1, j+1)*theApp.m_rightText[2] + theApp.m_rightText[5] *gray_img.at<uchar>(i, j + 1)
						+ theApp.m_rightText[8] *gray_img.at<uchar>(i+1, j + 1);;
				}

			}
			pixl_gray = abs(x1) + abs(x2);
			if(pixl_gray<0)
			{
				pixl_gray =0;
			}
			if(pixl_gray>255)
			{
				pixl_gray =255;
			}
			dstMat.at<uchar>(i, j) = (uchar)pixl_gray;
		}
	}
	
	ShowImage(dstMat);
	
	//m_last_filter =  m_choice;
	m_filterMat = dstMat;//保存高通滤波后的图，用于人脸分割
	//onFaceCutShow(dstMat);//进行人脸分割
	
	/*
    float prewittx[9] =             
    {    
        -1,0,1,    
        -1,0,1,    
        -1,0,1    
    };    
    float prewitty[9] =     
    {    
        1,1,1,    
        0,0,0,    
        -1,-1,-1    
    };    
    Mat px=Mat(3,3,CV_32F,prewittx);  
	cout<<px<<endl;
    Mat py=Mat(3,3,CV_32F,prewitty);  
	cout<<py<<endl;
    Mat dstx=Mat(gray_img.size(),gray_img.type(),gray_img.channels());  
    Mat dsty=Mat(gray_img.size(),gray_img.type(),gray_img.channels());  
    Mat dst=Mat(gray_img.size(),gray_img.type(),gray_img.channels());  
    filter2D(gray_img,dstx,gray_img.depth(),px);  
    filter2D(gray_img,dsty,gray_img.depth(),py);  
    float tempx,tempy,temp;  
    for(int i=0;i<gray_img.rows;i++)  
    {  
        for(int j=0;j<gray_img.cols;j++)  
        {  
            tempx=dstx.at<uchar>(i,j);  
            tempy=dsty.at<uchar>(i,j);  
            temp=sqrt(tempx*tempx+tempy*tempy); 
			if(temp<0)
			{
				temp =0;
			}
			if(temp>255)
			{
				temp =255;
			}
            dst.at<uchar>(i,j)=temp;  
        }  
    } 
	*/
	
}

void CPImageApp::OnRobertsShow()//空域锐化 roberts算子
{
	Mat imat = ReadImage();
	// 输入图像判断
    if (imat.empty())
        return;

	Mat src_blur,gray_img,dstMat;
	//GaussianBlur(imat, src_blur, Size(3, 3),0, 0, BORDER_DEFAULT);
	//int chanels = imat.channels();
	RGBtoGRAY(imat,gray_img);//RGB转换GRAY
	dstMat = gray_img.clone();

	int nRows = dstMat.rows;
	int nCols = dstMat.cols;
	int x1,x2,t1,t2;
	for (int i = 0; i < nRows - 1; i++){
		for (int j = 0; j < nCols - 1; j++){
			//根据公式计算
			int pixl_gray = 0;
			if(m_choice == IDM_ROBERTS )//Roberts算子
			{
				if(m_defalt_singlepatern == SINGLE_LEFT)
				{
					x1 = gray_img.at<uchar>(i, j)*theApp.m_leftText[0] + theApp.m_leftText[3] *gray_img.at<uchar>(i + 1, j + 1);
					x2 = 0;
				}
				else if(m_defalt_singlepatern == SINGLE_RIGHT)
				{
					x1 = 0;
					x2 = gray_img.at<uchar>(i+1, j)*theApp.m_rightText[2] +theApp.m_rightText[1]*gray_img.at<uchar>(i , j + 1);
				}
				else if(m_defalt_singlepatern == DOUBLE_PATREN)
				{
					x1 = gray_img.at<uchar>(i, j)*theApp.m_leftText[0] + theApp.m_leftText[3] *gray_img.at<uchar>(i + 1, j + 1);
					x2 = gray_img.at<uchar>(i+1, j)*theApp.m_rightText[2] +theApp.m_rightText[1]*gray_img.at<uchar>(i , j + 1);
				}
				

				
				
			}
			else if(m_choice == IDM_HORI_VERT)//s水平垂直算子
			{
				if(m_defalt_singlepatern == SINGLE_LEFT)
				{
					x1 = gray_img.at<uchar>(i, j)*theApp.m_leftText[0] + theApp.m_leftText[1] *gray_img.at<uchar>(i , j + 1);
					x2 = 0;
				}
				else if(m_defalt_singlepatern == SINGLE_RIGHT)
				{
					x1 = 0;
					x2 = gray_img.at<uchar>(i, j)*theApp.m_rightText[0] +theApp.m_rightText[2]*gray_img.at<uchar>(i+1 , j );
				}
				else if(m_defalt_singlepatern == DOUBLE_PATREN)
				{
					x1 = gray_img.at<uchar>(i, j)*theApp.m_leftText[0] + theApp.m_leftText[1] *gray_img.at<uchar>(i , j + 1);
					x2 = gray_img.at<uchar>(i, j)*theApp.m_rightText[0] +theApp.m_rightText[2]*gray_img.at<uchar>(i+1 , j );
				}

			}
			t1 = x1*x1;
			t2 = x2*x2;
			//计算g（x,y）
			pixl_gray = sqrt(t1 + t2);
			if(pixl_gray<0)
			{
				pixl_gray =0;
			}
			if(pixl_gray>255)
			{
				pixl_gray =255;
			}
			dstMat.at<uchar>(i, j) = (uchar)pixl_gray;
			
		}
	}
	ShowImage(dstMat);

}


void CPImageApp::OnLaFilterShow()//空域锐化 拉普拉斯算子
{
	Mat imat = ReadImage();
	// 输入图像判断
    if (imat.empty())
        return;

	Mat blur_dst,gray_img, dstMat;
	int chanels = imat.channels();
	
	RGBtoGRAY(imat,gray_img);//RGB转换GRAY
	dstMat = gray_img.clone();
	Mat srcMat = gray_img.clone();
	int nRows = dstMat.rows;
	int nCols = dstMat.cols;
	
	
	//动态数组
	int **logArr=new int *[nRows];

	int xy_ignore = theApp.m_modelMatrix/2;
	for (int i = 0; i < nRows; i++)
	{
		logArr[i]= new int[nCols];//为每行分配空间（每行中有col个元素）
		for (int j = 0; j <nCols; j++)
		{
			if(i-xy_ignore<0 ||i+xy_ignore>nRows )// MODE == 5时，前两行 ，最后两行会被过滤掉不计算 但保存值
			{
				logArr[i][j] = dstMat.at<uchar>(i, j);
				continue;
			}
			else if(j-xy_ignore<0 || j+xy_ignore>nCols) // MODE == 5时，前两列 ，最后两列会被过滤掉不计算 但保存值
			{
				logArr[i][j] = dstMat.at<uchar>(i, j);
				continue;
			}
			
			int countModelMatrix = 0;
			int sumWP = 0;//计算权重与像素灰度值之和
			for (int p = i-theApp.m_modelMatrix/2; p <=i+ theApp.m_modelMatrix/2; p++)//小模板内
			{	
				for (int q = j-theApp.m_modelMatrix/2; q <=j+ theApp.m_modelMatrix/2; q++)
				{
					countModelMatrix ++;
					if(p<0 || q<0 || p>nRows-1 ||q> nCols-1)
					{
						continue;
					}
					else
					{
						int w = theApp.m_text[countModelMatrix-1];
						int p_gray = srcMat.at<uchar>(p, q);
						sumWP +=  w * p_gray;//计算权重与像素灰度之和
					}
				}
			}
			int pixl_gray = sumWP; //得到计算完的灰度值
			if(m_choice == IDM_LA_FILTER || m_choice ==IDM_LA_GRAY)//基于高斯型拉普拉斯算子
			{
				if(pixl_gray<0)
				{
					pixl_gray =0;
				}
				//if(pixl_gray>0)
				if(pixl_gray>255)
				{
					pixl_gray =255;
				}
			}
			logArr[i][j] = pixl_gray;
			dstMat.at<uchar>(i, j) = pixl_gray;
			/*
			if(m_choice == IDM_LA_GRAY)
			{
				pixl_gray = sumWP + gray_img.at<uchar>(i, j);
				if(pixl_gray>255)
				{
					pixl_gray =255;
				}
				dstMat.at<uchar>(i, j) = pixl_gray;
			}*/
		}
	}
	if(m_choice == IDM_LA_GRAY)
	{
		int media = theApp.m_modelMatrix*theApp.m_modelMatrix/2;
		//int a = theApp.m_text[ media];
		if(theApp.m_text[ media]< 0)//如果拉普拉斯模板具有副的中心系数，则用原图减掉 拉普拉斯变换后的图像
		{
			dstMat=srcMat - dstMat;
		}
		else //如果拉普拉斯模板具有正的中心系数，则用原图加上 拉普拉斯变换后的图像
		{
			dstMat=srcMat + dstMat;
		}
	}
	
	
}

void CPImageApp::OnMaxFilterShow()//空域最大值滤波 最大值滤波的输出值是邻域内像素的最亮点，因此，最大值滤波能够有效地滤除椒噪声
								//最小值滤波输出是邻域内像素的最暗点，因此，最小值滤波能够有效地滤除盐噪声
{
	Mat imat = ReadImage();
	// 输入图像判断
    if (imat.empty())
        return;

	saltAndPeper(imat,256);
	cv::imshow("加入椒盐噪声后的图片",imat);

	Mat gray_img,dstMat;
	int chanels = imat.channels();
	RGBtoGRAY(imat,gray_img);//RGB转换GRAY
	int nRows = gray_img.rows;
	int nCols = gray_img.cols;
	Mat dst = Mat::zeros(nRows,nCols, CV_8U);

	int max_min; //

	//最大值滤波操作
	for (int i = 0; i < nRows - 1; i++)
	{
		for (int j = 0; j <nCols - 1; j++)
		{
			
			if(m_choice == IDM_MIN) //最小值滤波
			{
				max_min = 255;
			}
			else if(m_choice == IDM_MAX_FILTER)//最大值滤波
			{
				max_min = 0; //如果是最小值滤波则初始化max_min=255;
			}
			int countModelMatrix = 0;
			for (int p = i-theApp.m_modelMatrix/2; p <=i+ theApp.m_modelMatrix/2; p++)//小模板内
			{	
				for (int q = j-theApp.m_modelMatrix/2; q <=j+ theApp.m_modelMatrix/2; q++)
				{
					countModelMatrix ++;
					if(p<0 || q<0 || p>nRows-1 ||q> nCols-1)
					{
						continue;
					}
					else
					{
						if(m_choice == IDM_MIN) //最小值滤波
						{
							if (max_min>gray_img.at<uchar>(p, q))//如果是最小值滤波，小于号改成大于号就可
							max_min = gray_img.at<uchar>(p, q);
						}
						else if(m_choice == IDM_MAX_FILTER)//最大值滤波
						{
							if (max_min<gray_img.at<uchar>(p, q))//如果是最小值滤波，小于号改成大于号就可
							max_min = gray_img.at<uchar>(p, q);
						}
						
					}
				}
			}
			dst.at<uchar>(i, j) = max_min;
		}
	}
	ShowImage(dst);
}

void CPImageApp::OnMedianFilterShow()//空域中值滤波
{
	Mat imat = ReadImage();
	// 输入图像判断
    if (imat.empty())
        return;
	saltAndPeper(imat,256);
	//salt(imat,3000);//加入盐噪声255
	//pepper(imat,3000);//加入椒噪声0
 
	// display result
	cv::imshow("加入椒盐噪声后的图片",imat);
	//imwrite(_T("C:/Users/Administrator/Desktop/图像处理/jiaoyan.png"),imat);
 
	//median filte
	Mat resutl;
	int ksize = theApp.m_modelMatrix;
	medianBlur(imat,resutl,ksize);
	ShowImage(resutl);
}

void CPImageApp::OnAverageFilterShow()//空域均值滤波
{
	Mat imat = ReadImage();
	// 输入图像判断
    if (imat.empty())
        return;

	//获取模板矩阵以及内容
	//CSmoothDlg sm;
	//m_modelMatrix = sm.getMatrix();
	//sm.getText(m_text);

	Mat gray_img,dstMat;
	int chanels = imat.channels();
	RGBtoGRAY(imat,gray_img);//RGB转换GRAY
	int nRows = gray_img.rows;
	int nCols = gray_img.cols;
	dstMat = gray_img.clone();

	int textSum =0;
	for(int i=0; i<theApp.m_modelMatrix*theApp.m_modelMatrix; i++)
	{
		textSum += theApp.m_text[i];
	}

	
	for (int i = 0; i < nRows - 1; i++)
	{
		for (int j = 0; j <nCols - 1; j++)//大的图片
		{
			int countModelMatrix = 0;
			int sumWP = 0;//计算权重与像素灰度值之和
			for (int p = i-theApp.m_modelMatrix/2; p <=i+ theApp.m_modelMatrix/2; p++)//小模板内
			{	
				for (int q = j-theApp.m_modelMatrix/2; q <=j+ theApp.m_modelMatrix/2; q++)
				{
					countModelMatrix ++;
					if(p<0 || q<0 || p>nRows-1 ||q> nCols-1)
					{
						continue;
					}
					else
					{
						int w = theApp.m_text[countModelMatrix-1];
						int p_gray = gray_img.at<uchar>(p, q);
						sumWP +=  w * p_gray;//计算权重与像素灰度之和
						
					}
				}
			}
			int pixl_gray = sumWP/textSum; //得到计算完的灰度值
			dstMat.at<uchar>(i, j) = pixl_gray;
		}
	}
	//imshow("",dstMat);
	//waitKey(0);

    //blur(imat, out, Size(3, 3)); 
	ShowImage(dstMat);
}
/*
void CPImageApp::OnFilterSmoothShow()//空域平滑处理
{

}*/
/**
 * @brief HistSpecify 对灰度图像进行直方图规定化
 * @param gray_img 输入图像
 * @param ref_img 参考图像，解析参考图像的直方图并用于规定化
 * @param res_img 直方图规定化后的图像
 * @note 手动设置一个直方图并用于规定化比较麻烦，这里使用一个参考图像来进行
 */
void CPImageApp::OnHistogramRegularizationShow()//直方图规定化
{
	Mat imat = ReadImage();
	// 输入图像判断
    if (imat.empty())
        return;

	Mat gray_img,ref_img,res_img;
	RGBtoGRAY(imat,gray_img);//原图RGB转换GRAY

	//判断文件名
	
	//m_openFilePath = m_guidinghuaPath;
	//Mat ref = ReadImage();
	if(!m_image.IsNull())
	{
		m_image.Destroy();
	}
	m_image.Load(m_guidinghuaPath);
	if(m_image.IsNull())
	{
		cout<<"error";
	}
	Mat ref;
	CImageToMat(m_image,ref);
	// 输入图像判断
    if (ref.empty())
        return;
	RGBtoGRAY(ref,ref_img);//目标图RGB转换GRAY

	res_img = gray_img.clone();//最终图


    Histogram1D hist1D;
    Mat src_hist = hist1D.getHistogram(gray_img);
    Mat dst_hist = hist1D.getHistogram(ref_img);

    float src_cdf[256] = { 0 };
    float dst_cdf[256] = { 0 };

    // 直方图进行归一化处理
    src_hist /= (gray_img.rows * gray_img.cols);
    dst_hist /= (ref_img.rows * ref_img.cols);

    // 计算原始直方图和规定直方图的累积概率
    for (int i = 0; i < 256; i++)
    {
        if (i == 0)
        {
            src_cdf[i] = src_hist.at<float>(i);
            dst_cdf[i] = dst_hist.at<float>(i);
        }
        else
        {
            src_cdf[i] = src_cdf[i - 1] + src_hist.at<float>(i);
            dst_cdf[i] = dst_cdf[i - 1] + dst_hist.at<float>(i);
        }
    }

    // 累积概率的差值
    float diff_cdf[256][256];
    for (int i = 0; i < 256; i++)
        for (int j = 0; j < 256; j++)
            diff_cdf[i][j] = fabs(src_cdf[i] - dst_cdf[j]);

    // 构建灰度级映射表
    Mat lut(1, 256, CV_8U);
    for (int i = 0; i < 256; i++)
    {
        // 查找源灰度级为ｉ的映射灰度
        //　和ｉ的累积概率差值最小的规定化灰度
        float min = diff_cdf[i][0];
        int index = 0;
        for (int j = 1; j < 256; j++)
        {
            if (min > diff_cdf[i][j])
            {
                min = diff_cdf[i][j];
                index = j;
            }
        }
        lut.at<uchar>(i) = static_cast<uchar>(index);
    }

    // 应用查找表，做直方图规定化
    LUT(gray_img, lut, res_img);

	Histogram1D hist3;
    Mat histImg_src = hist3.getHistogramImage(gray_img,m_choice);//原图
    Histogram1D hist4;
    Mat histImg_ref = hist4.getHistogramImage(ref_img,m_choice);//目标图
    Histogram1D hist5;
    Mat histImg_res = hist5.getHistogramImage(res_img,m_choice);//结果正规化图

	//imshow("原图", gray_img);
    imshow("原图直方图", histImg_src);
    //imshow("目标图", ref_img);
    imshow("目标直方图", histImg_ref);
	ShowImage(res_img);
    //imshow("直方图规定化后图像", res_img);
    imshow("规定化后直方图", histImg_res);



}

void CPImageApp::OnHistogramEqualizationShow()//直方图均衡化
{
	
	//imshow("",writeImage);

}

void CPImageApp::OnHistogramGrayShow()//显示直方图 //直方图均衡化
{
	Mat imat = ReadImage();
	// 输入图像判断
    if (imat.empty())
        return;
	
	Mat gray_img;
	RGBtoGRAY(imat,gray_img);//RGB转换GRAY
	Mat writeImage;
	if(m_choice == ID_HISTOGRAM_EQUALIZATION)//如果是直方图均衡化
	{
		vector<Mat>channelImage;
		split(gray_img,channelImage);

		for(int i = 0; i< gray_img.channels(); i++)
		{
			equalizeHist(channelImage[i], channelImage[i]);//直方图均衡化
		}

		merge(channelImage, writeImage);
		ShowImage(writeImage);
		Histogram1D hist4;
		Mat histImg_ref = hist4.getHistogramImage(writeImage,m_choice);//目标图
		imshow("均衡化直方图", histImg_ref);
	}
	Histogram1D hist3;
    Mat histImg_src = hist3.getHistogramImage(gray_img,m_choice);//原图
   
   // Histogram1D hist5;
   // Mat histImg_res = hist5.getHistogramImage(res_img);//结果正规化图

	imshow("原图直方图", histImg_src);
   // imshow("目标图", ref_img);
   // imshow("目标直方图", histImg_ref);
	//ShowImage(res_img);
    //imshow("直方图规定化后图像", res_img);
  //  imshow("规定化后直方图", histImg_res);
	/*
	int arr_size = 255;
	const int channels[1] = { 0 };
    const int histSize[1] = { 256 };
    float hranges[] = { 0, 255 };
    float* ranges = hranges;
	CvHistogram *hist = cvCreateHist(1, &arr_size, CV_HIST_ARRAY, &ranges, 1);	//创建一个一维的直方图，行宽为255，多维密集数组，方块范围为0-255，bin均化
    IplImage * histimg  = cvCreateImage(cvSize(320, 200), 8, 3);
	cvZero(histimg);    //清空histimag-imagedata数据
	IplImage * ipl;
	if(m_choice == ID_HISTOGRAM_EQUALIZATION)//如果是直方图均衡化
	{
		ipl = cvCloneImage(&(IplImage)writeImage);
	}
	else
	{
		ipl = cvCloneImage(&(IplImage)gray_img);
	}
	cvCalcHist(&ipl, hist, 0, 0); 
	
	float max_val;	//用于存储获取到的最大值
	cvGetMinMaxHistValue(hist, 0, &max_val, 0, 0);	//获取直方图最大值
	cvConvertScale(hist->bins,hist->bins, max_val ? 255. / max_val : 0., 0);	//按比例缩小直方图

	int bin_w;
	bin_w = histimg->width / arr_size; //得到开始绘制点位置
 
	for (int i = 0; i < arr_size; i++)
	{
		double val = (cvGetReal1D(hist->bins, i)*histimg->height / 255);//获取矩阵元素值，并转换为对应高度
		CvScalar color = CV_RGB(255, 255, 0);                                 				
		cvRectangle(histimg, cvPoint(i*bin_w, histimg->height),
		cvPoint((i + 1)*bin_w, (int)(histimg->height - val)),
			color, 1, 8, 0);
	}
	Mat mat = cvarrToMat(histimg);
	if(m_choice == ID_HISTOGRAM_EQUALIZATION)
	{
		imshow("直方图均衡化",mat);
		//imwrite(_T("C:/Users/Administrator/Desktop/图像处理/hh.png"),mat);
	}
    else
	{
		imshow("直方图原图",mat);
		
	}
	*/
}
/*
void CPImageApp::OnPowerShow()//对数变换
{
	Mat imat = ReadImage();
	// 输入图像判断
    if (imat.empty())
        std::cout << "No data!" << std::endl;
	Mat gray_img;
	RGBtoGRAY(imat,gray_img);//RGB转换GRAY
}
*/
void CPImageApp::OnLogTransform()//对数变换
{
	Mat imat = ReadImage();
	// 输入图像判断
    if (imat.empty())
        std::cout << "No data!" << std::endl;
	Mat gray_img;
	int channels = imat.channels();
	RGBtoGRAY(imat,gray_img);//RGB转换GRAY
    cv::Mat resultImage =cv::Mat::zeros(gray_img.size(), gray_img.type());
    // 计算 1 + r
    cv::add(gray_img, cv::Scalar(1.0), gray_img);
    // 转换为32位浮点数
    gray_img.convertTo(gray_img, CV_32F);
    // 计算 log(1 + r)
    log(gray_img, resultImage);
	int c = theApp.m_text[0];
    resultImage = c * resultImage;
    // 归一化处理
    cv::normalize(resultImage, resultImage,
        0, 255, cv::NORM_MINMAX);
    cv::convertScaleAbs(resultImage, resultImage);
	ShowImage(resultImage);
}
void CPImageApp::OnAnticolorChange()
{
	Mat imat = ReadImage();
	Mat dstImg = GRAY_LEVEL - imat;
	ShowImage(dstImg);
}

void CPImageApp::OnPiecewiseLinearTransform()
{
	Mat imat = ReadImage();
	Mat gray_img;
	int channels = imat.channels();
	RGBtoGRAY(imat,gray_img);//RGB转换GRAY
	if(m_choice == IDM_DSCRETCH || m_choice == IDM_LAYER)
	{
		 //获取图片的一些属性  
		int RowsNum = imat.rows;
		int ColsNum = imat.cols;
		float k, b;//斜率
		//int channels = imat.channels();
		uchar *srcData = gray_img.ptr<uchar>(0);
		float max = srcData[0], min = srcData[0], mean = srcData[0] ;
		for (int i = 0; i < RowsNum; i++)
		{
			uchar *srcData = gray_img.ptr<uchar>(i);
			for (int j = 0; j < ColsNum; j++)
			{
				if(srcData[j]>max)
				{
					max = srcData[j];
				}
				else if (srcData[j]<min)
				{
					min = srcData[j];
				}
			}
		}
		
		Mat dstImg(gray_img.size(), gray_img.type());
		//进行遍历图像像素,对每个像素进行相应的线性变换
		float x1 = 0,x2 = 0;
		float k1 = 0.0,b1 =0.0,k2 =0.0,b2 =0.0,k3 = 0.0,b3 = 0.0;
		if(m_choice == IDM_DSCRETCH)
		{
		
		if(theApp.m_default)
		{
			k = 255/(max-min);
			b = -min*k;
		}
		else
		{
			x1 = theApp.m_text[0];
			float y1 = theApp.m_text[1];
			x2 = theApp.m_text[2];
			float y2 = theApp.m_text[3];
			if(x1 != 0)
			{
				k1 = y1/x1;
				b1 = 0;
			}
			k2 = (y2-y1)/(x2-x1);
			b2 = -x1*k2 + y1;
			if(255-x2 != 0)
			{
				k3 = (255-y2)/(255-x2);
				b3 = -x2*k3 + y2;
			}
			/*
			k = (y2-y1)/(x2-x1);
			b = -x1*k + y1;*/
		}
		}
		
		/*
		k = 255/(max-min);
		b = -min*k;
		*/
		for (int i = 0; i < RowsNum; i++)
		{
			uchar *srcData = gray_img.ptr<uchar>(i);
			for (int j = 0; j < ColsNum; j++)
			{
			
				if(m_choice == IDM_DSCRETCH) //对比度拉伸
				{
					if(theApp.m_default == false)
					{
						if( 0<=srcData[j]<x1)
						{
							dstImg.at<uchar>(i, j) = srcData[j] * k1 + b1;
						}
						else if(x1<= srcData[j]<x2)
						{
							dstImg.at<uchar>(i, j) = srcData[j] * k2 + b2;
						}
						else if(x2<=srcData[j]<255)
						{
							dstImg.at<uchar>(i, j) = srcData[j] * k3 + b3;
						}
					}
					else
					{
						dstImg.at<uchar>(i, j) = srcData[j] * k + b;
					}
					
					/*
					if(channels != 1)
					{
						float aa = srcData[j] * k + b;
						dstImg.at<cv::Vec3b>(i, j)[0] = aa;
						dstImg.at<cv::Vec3b>(i, j)[1] = aa;
						dstImg.at<cv::Vec3b>(i, j)[2] = aa;
						//for (int nCha = 0 ; nCha < channels; nCha++)
							//dstImg.at<cv::Vec3b>(i, j)[nCha] = srcData[j] * k + b;
					}
					else
					{
						dstImg.at<uchar>(i, j) = srcData[j] * k + b;
					}
					*/
				}
				else if(m_choice == IDM_LAYER) //灰度级分层
				{
					if(srcData[j] <= 125)
					{
						dstImg.at<uchar>(i, j) = 255;
					}
					
					else
					{
						dstImg.at<uchar>(i, j) = 0;
						/*
						if(channels != 1)
						{
							dstImg.at<cv::Vec3b>(i, j)[0] = 0;
							dstImg.at<cv::Vec3b>(i, j)[1] = 0;
							dstImg.at<cv::Vec3b>(i, j)[2] = 0;
							//for (int nCha = 0 ; nCha < channels; nCha++)
							//	dstImg.at<cv::Vec3b>(i, j)[nCha] = 0;
						}
						else
						{
							dstImg.at<uchar>(i, j) = 0;
						}
						*/
					}
				
				}
			}
		}
		//imwrite(_T("C:/Users/Administrator/Desktop/图像处理/lena_lowgray.png"),dstImg);	
		ShowImage(dstImg);
	}

}
void CPImageApp::OnDCTTransform(int choice)
{
	Mat imat = ReadImage();
	int m = getOptimalDFTSize(imat.rows);
    int n = getOptimalDFTSize(imat.cols);
	int chanels = imat.channels();
	Mat gray_img;
	RGBtoGRAY(imat,gray_img);//RGB转换GRAY
	Mat srcDCT; 
    resize(gray_img, gray_img, Size(n, m));
    gray_img.convertTo(gray_img, CV_32F, 1.0/255);
	dct(gray_img, srcDCT);
	if(choice == IDM_DCTR)
	{
		int h=srcDCT.size[0];
		int w = srcDCT.size[1];
		cv::Size s(w,h);
		cv::Mat idctimage=cv::Mat::zeros(h,w,CV_32F);
	
		int left_h = 0;
		int left_w = 0;
		for (int i = left_h; i < srcDCT.rows;i++)
			for (int j = left_w; j < srcDCT.cols; j++)
			{
				idctimage.at<float>(i, j) = srcDCT.at<float>(i, j);

			}
		
		idct(idctimage, idctimage);  //离散余弦逆变换
		idctimage.convertTo(idctimage, CV_8UC1, 255, 0); 
		ShowImage(idctimage);
		//cv::imshow("view", idctimage);
	}
	if(choice == IDM_DCT)
	{
		srcDCT.convertTo(srcDCT, CV_8UC1, 255, 0);
		ShowImage(srcDCT);
		//cv::imshow("view", srcDCT);
	}
	
   
}

void CPImageApp::OnFourierTransform(/*Mat mat,*/int choice/*,int posx, int posy*/)//傅里叶变换
{
	Mat imat;
	Mat gray_img;
	Mat padded;                 //以0填充输入图像矩阵
	//加载图片
	imat = ReadImage();
	RGBtoGRAY(imat,gray_img);//RGB转换GRAY

	int m = getOptimalDFTSize(imat.rows);
	int n = getOptimalDFTSize(imat.cols);

    //填充输入图像imat，输入矩阵为padded，上方和左方不做填充处理
    copyMakeBorder(gray_img, padded, 0, m - gray_img.rows, 0, n - gray_img.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(),CV_32F) };
    Mat complexI;
    merge(planes, 2, complexI);     //将planes融合合并成一个多通道数组complexI
	dft(complexI, complexI);        //进行傅里叶变换
	split(complexI, planes);        //planes[0] = Re(DFT(I),planes[1] = Im(DFT(I))
                                  //即planes[0]为实部,planes[1]为虚部
    magnitude(planes[0], planes[1], planes[0]);     //planes[0] = magnitude
    Mat magI = planes[0];
    magI += Scalar::all(1);
    log(magI, magI);                //转换到对数尺度(logarithmic scale)

    //如果有奇数行或列，则对频谱进行裁剪
    magI = magI(Rect(0, 0, magI.cols&-2, magI.rows&-2));
    //重新排列傅里叶图像中的象限，使得原点位于图像中心
    int cx = magI.cols / 2;
    int cy = magI.rows / 2;

    Mat q0(magI, Rect(0, 0, cx, cy));       //左上角图像划定ROI区域
    Mat q1(magI, Rect(cx, 0, cx, cy));      //右上角图像
    Mat q2(magI, Rect(0, cy, cx, cy));      //左下角图像
    Mat q3(magI, Rect(cx, cy, cx, cy));     //右下角图像

    //变换左上角和右下角象限
    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    //变换右上角和左下角象限
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
	
	planes[0]+=Scalar::all(1);//傅立叶变换后的图片不好分析，进行对数处理，结果比较好看
	log(planes[0],planes[0]);
    //归一化处理，用0-1之间的浮点数将矩阵变换为可视的图像格式
    normalize(magI, magI, 0, 1, CV_MINMAX);
	magI.convertTo(magI, CV_8UC1, 255, 0);
	ShowImage(magI);
	if(choice == IDM_FR)
	{
		Mat _complexim;
		complexI.copyTo(_complexim);//把变换结果复制一份，进行逆变换，也就是恢复原图
		Mat iDft[]={Mat::zeros(planes[0].size(),CV_32F),Mat::zeros(planes[0].size(),CV_32F)};//创建两个通道，类型为float，大小为填充后的尺寸
		idft(_complexim,_complexim);//傅立叶逆变换
		split(_complexim,iDft);//结果貌似也是复数
		magnitude(iDft[0],iDft[1],iDft[0]);//分离通道，主要获取0通道
		normalize(iDft[0],iDft[0],1,0,CV_MINMAX);//归一化处理，float类型的显示范围为0-1,大于1为白色，小于0为黑色
		iDft[0].convertTo(iDft[0], CV_8UC1, 255, 0);
		//cvtColor(iDft[0],iDft[0],CV_GRAY2RGB);
		ShowImage(iDft[0]);
		//imwrite(_T("C:/Users/Administrator/Desktop/图像处理/lena_big.png"),iDft[0]);
		//imwrite(_T("C:\\sample1024.bmp"),iDft[0]);
		//imshow("view", iDft[0]);
	}
  
	
}

// CPImageApp 消息处理程序



void CPImageApp::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CPImageApp::OnBnClicked2()
{
	// TODO: 在此添加控件通知处理程序代码
}


CSTRETCHDlg::CSTRETCHDlg(void)
{
}


CSTRETCHDlg::~CSTRETCHDlg(void)
{
}

void CPImageApp::OnGltLogarithm()//对数变换
{
	m_choice = IDM_GLT_LOGARITHM;
	CLogDlg dlg;
	dlg.setDlgTitle("对数变换",IDM_GLT_LOGARITHM);
	dlg.DoModal();
	OnMenu();
		
}


void CPImageApp::OnHistogramGray()//灰度直方图
{
	m_choice = IDM_HISTOGRAM_GRAY;
	OnMenu();
}


void CPImageApp::OnHistogramEqualization()//直方图均衡化
{
	m_choice = IDM_HISTOGRAM_EQUALIZATION;
	OnMenu();
	
}


void CPImageApp::OnHistogramRegularization()
{
	m_choice = IDM_HISTOGRAM_REGULARIZATION;
	OnMenu();
	
}




/*
void CPImageApp::OnFilterSmooth()
{
	m_choice = IDM_FILTER_SMOOTH;
	OnMenu();
}
*/

void CPImageApp::OnAverageFilter()
{
	m_choice = IDM_AVERAGE_FILTER;
	CSmoothDlg dlg;
	dlg.setDlgTitle("均值滤波",IDM_AVERAGE_FILTER);
	dlg.DoModal();
	
	OnMenu();
}


void CPImageApp::OnMedianFilter()
{
	m_choice = IDM_MEDIAN_FILTER;
	CSmoothDlg dlg;
	dlg.setDlgTitle("中值滤波",IDM_MEDIAN_FILTER);
	dlg.DoModal();
	OnMenu();
}

void CPImageApp::OnMaxFilter()
{
	m_choice = IDM_MAX_FILTER;
	CSmoothDlg dlg;
	dlg.setDlgTitle("最大值滤波",IDM_MAX_FILTER);
	dlg.DoModal();
	OnMenu();
}

void CPImageApp::OnMin()
{
	m_choice = IDM_MIN;
	CSmoothDlg dlg;
	dlg.setDlgTitle("最小值滤波",IDM_MIN);
	dlg.DoModal();
	OnMenu();
}

void CPImageApp::OnLaFilter()
{
	m_choice = IDM_LA_FILTER;
	CSmoothDlg dlg;
	dlg.setDlgTitle("拉普拉斯算子",IDM_LA_FILTER);
	dlg.DoModal();
	OnMenu();
}

void CPImageApp::OnLaGray()
{
	m_choice = IDM_LA_GRAY;
	CSmoothDlg dlg;
	dlg.setDlgTitle("拉普拉斯算子加原图",IDM_LA_GRAY);
	dlg.DoModal();
	OnMenu();
}


void CPImageApp::OnHoriVert()
{
	m_choice = IDM_HORI_VERT;
	CSharpenDlg dlg;
	dlg.setDlgTitle("水平垂直算子",IDM_HORI_VERT);
	dlg.DoModal();
	//CSmoothDlg dlg;
	//dlg.setDlgTitle("水平垂直算子",IDM_HORI_VERT);
	OnMenu();
}

void CPImageApp::OnRoberts() ////空域锐化 Roberts 算子
{
	m_choice = IDM_ROBERTS;
	CSharpenDlg dlg;
	dlg.setDlgTitle(" Roberts 算子",IDM_ROBERTS);
	dlg.DoModal();
	OnMenu();
}


void CPImageApp::OnPrewitt()
{
	m_choice = IDM_PREWITT;
	CSharpenDlg dlg;
	dlg.setDlgTitle("Prewitt 算子",IDM_PREWITT);
	dlg.DoModal();
	OnMenu();
}


void CPImageApp::OnSobel()
{
	
	m_choice = IDM_SOBEL;
	CSharpenDlg dlg;
	dlg.setDlgTitle("Sobel 算子",IDM_SOBEL);
	dlg.DoModal();
	OnMenu();
}

void CPImageApp::OnTest()
{
	CSmoothDlg dlg;
	dlg.DoModal();
}


void CPImageApp::OnIlpf()
{
	m_choice = IDM_ILPF;
	CFFilterDlg dlg;
	dlg.setDlgTitle("理想低通滤波器",IDM_ILPF);
	dlg.DoModal();
	OnMenu();
}
void CPImageApp::OnIhpf()
{
	m_choice = IDM_IHPF;
	CFFilterDlg dlg;
	dlg.setDlgTitle("理想高通滤波器",IDM_IHPF);
	dlg.DoModal();
	OnMenu();
	
}

void CPImageApp::OnBlpf()
{
	m_choice = IDM_BLPF;
	CFFilterDlg dlg;
	dlg.setDlgTitle("布特沃斯低通滤波器",IDM_BLPF);
	dlg.DoModal();
	OnMenu();
}


void CPImageApp::OnBhpf()
{
	m_choice = IDM_BHPF;
	CFFilterDlg dlg;
	dlg.setDlgTitle("布特沃斯高通滤波器",IDM_BHPF);
	dlg.DoModal();
	OnMenu();
}


void CPImageApp::OnGlpf()//高斯低通滤波
{
	m_choice = IDM_GLPF;
	CFFilterDlg dlg;
	dlg.setDlgTitle("高斯低通滤波",IDM_GLPF);
	dlg.DoModal();
	OnMenu();
}


void CPImageApp::OnGhpf()
{
	m_choice = IDM_GHPF;
	CFFilterDlg dlg;
	dlg.setDlgTitle("高斯高通滤波",IDM_GHPF);
	dlg.DoModal();
	OnMenu();
	
}



void CPImageApp::OnLight()
{
	m_choice = IDM_LIGHT;
	OnMenu();
}



