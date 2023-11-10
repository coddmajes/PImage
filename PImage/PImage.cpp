
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
#include "DegeDlg.h"

#include "cv.h"
#include "highgui.h"
#include <math.h>
#include <atlstr.h>
#include <string> 

//#include "opencv.hpp"


using namespace std;
using namespace cv;

#define GRAY_LEVEL 255
#define REVERSE -1
#define LEFT 1
#define RIGHT 0
#define VERTICAL 3
#define HORIZON 4
#define ALL_R 2
#define ALL_VH 5



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
	ON_COMMAND(ID_WHITE, &CPImageApp::OnWhite)
	ON_COMMAND(ID_SCRESHOT, &CPImageApp::OnScreshot)
	ON_COMMAND(ID_FRESTORE, &CPImageApp::OnFrestore)
	ON_COMMAND(ID_RESTOREFUC, &CPImageApp::OnRestorefuc)
	ON_COMMAND(ID_REVERFILTER, &CPImageApp::OnReverfilter)
	ON_COMMAND(ID_THRESHOLD, &CPImageApp::OnThreshold)
	ON_COMMAND(ID_GLOBAL_THRESHOLD, &CPImageApp::OnGlobalThreshold)
	ON_COMMAND(ID_OTSU_THRESHOLD, &CPImageApp::OnOtsuThreshold)
	ON_COMMAND(ID_EDGE_DETECT, &CPImageApp::OnEdgeDetect)
	ON_COMMAND(ID_EDGE_SOBEL, &CPImageApp::OnEdgeSobel)
	ON_COMMAND(ID_EDGE_LAPLA, &CPImageApp::OnEdgeLapla)
	ON_COMMAND(ID_EDGE_LOG, &CPImageApp::OnEdgeLog)
	ON_COMMAND(ID_EDGE_HOUGH, &CPImageApp::OnEdgeHough)
	ON_COMMAND(ID_EDGE_CANNY, &CPImageApp::OnEdgeCanny)
	ON_COMMAND(ID_FIELD_GROW, &CPImageApp::OnFieldGrow)
	ON_COMMAND(ID_FIELD_SPO, &CPImageApp::OnFieldSpo)
	ON_COMMAND(ID_FACE_CUT, &CPImageApp::OnFaceCut)
	ON_COMMAND(ID_CUT_TAG, &CPImageApp::OnCutTag)
	ON_COMMAND(ID_FACE_THRE, &CPImageApp::OnFaceThre)
	ON_COMMAND(ID_FACE_EDGE, &CPImageApp::OnFaceEdge)
	ON_COMMAND(ID_FACE_FCUT, &CPImageApp::OnFaceFcut)
	ON_COMMAND(ID_FACE_TAG, &CPImageApp::OnFaceTag)
	ON_COMMAND(ID_FACE_TOP, &CPImageApp::OnFaceTop)
	ON_COMMAND(ID_FACE_LEFT, &CPImageApp::OnFaceLeft)
	ON_COMMAND(ID_FACE_RIGHTC, &CPImageApp::OnFaceRight)
	ON_COMMAND(ID_FACE_NOSE, &CPImageApp::OnFaceNose)
	ON_COMMAND(ID_FACE_BOTTOM, &CPImageApp::OnFaceBottom)
	ON_COMMAND(ID_FILE_SAVE_A, &CPImageApp::OnFileSave)
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

void CPImageApp::OnFileSave()
{
	TCHAR szFilter[] = _T("JPG图片(*.jpg)|*.jpg|BMP图片(*.bmp)|*.bmp|PNG图片(*.png)|*.png|JPEG图片(*.jpeg)|*.jpeg|DIB图片(*dib)|*.dib|PBM图片(*.pbm)|*.pbm|GIF图片(*.gif)|*.gif||");
    // 构造保存文件对话框   
    CFileDialog fileDlg(FALSE, _T("bmp"), _T("New"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
    CString strFilePathName , strFilePath, strFileName;
    // 显示保存文件对话框   
    if (IDOK == fileDlg.DoModal())
    {
        // 如果点击了文件对话框上的“保存”按钮，则将选择的文件路径显示到编辑框里   
        strFilePathName = fileDlg.GetPathName();
		strFilePath = fileDlg.GetFolderPath();
		strFileName = fileDlg.GetFileName();
    }
    vector<int> compression_params;
	std::string STDPathStr = CT2A(strFilePathName.GetBuffer());
	std::string STDStr = CT2A(strFilePath.GetBuffer());
	std::string STDFileNameStr = CT2A(strFileName.GetBuffer());
    //std::string STDStr = (CW2A(strFilePath.GetString()));
	//imwrite(STDStr, m_savePic[m_recoverNum-1], compression_params);
	if(m_savePics.empty() || m_savePic[0].empty())
	{
		return;
	}
	if(m_recoverNum>0)
	{
		for(int i = 0; i<m_recoverNum;i++)
		{
			 imwrite(STDStr+"\\"+ STDFileNameStr+to_string(i)+".bmp", m_savePic[i]);//, compression_params);
		}
	}
	else
	{
		 imwrite(STDPathStr, m_savePics);//, compression_params);
	}
	
   
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
			if(!m_leftImage.IsNull())
			{
				m_leftImage.Destroy();
			}
			m_leftImage.Load(m_openFilePath);
			mf->GetLeftPane()->setImage(m_leftImage);
			mf->GetLeftPane()->Invalidate(TRUE);
		}
		
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
        cv::calcHist(&image ,// 要计算图像的
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
	m_odk = false;
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
		case IDM_DSCRETCH:
			OnPiecewiseLinearTransform();//对比度拉伸
			break;
		case IDM_LAYER:
			OnPiecewiseLinearTransform();//灰度级变换
			break;
		case IDM_BIT_LAYER:
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
		case IDM_WHITE:
			OnLightShow();//白线
			break;
		case IDM_SCRESHOT:
			OnLightShow();//截取区域
			break;
		case IDM_FRESTORE:
			OnLightShow();//区域复原
			break;
		case IDM_RESTOREFUC:
			OnLightShow();//退化函数
			break;
		case IDM_REVERFILTER:
			OnLightShow();//逆滤波复原
			break;
		case IDM_GLOBAL_THRESHOLD:
			OnThresholdShow(); //基本全局阈值处理
			break;
		case IDM_OTSU_THRESHOLD:
			OnThresholdShow(); //OTSU最佳阈值处理
			break;
		case IDM_EDGE_LOG:
			OnLaFilterShow(); //基于边缘检测
			break;
		case IDM_EDGE_CANNY:
			OnEdgeCannyShow(); //canny算子 
			break;
		case IDM_EDGE_HOUGH:
			OnEdgeCannyShow(); //边缘连接
			break;
		case IDM_FIELD_GROW:
			OnFieldGrowShow();//区域生长
			break;
		case IDM_FIELD_SPO:
			OnFieldSpoShow(); //区域分裂与聚合
			break;
		case IDM_FACE_CUT:
			onFaceCutShow();//进行人脸分割
			break;
		case IDM_FACE_THRE:
			onFaceCutShow();//人脸分割--阈值处理
			break;
		case IDM_FACE_EDGE:
			onFaceCutShow();//人脸分割--边缘检测
			break;
		case IDM_FACE_FCUT:
			onFaceCutShow();//人脸分割--图片分割
			break;
		case IDM_FACE_TAG:
			onFaceCutShow();//人脸分割--分割标记
			break;
		case IDM_CUT_TAG:
			OnCutTagShow();//记性分割标记
			break;

		case IDM_FACE_TOP://提取额头
			OnFaceExtraShow();//脸部分割
			break;
		case IDM_FACE_LEFT://提取左脸颊
			OnFaceExtraShow();//脸部分割
			break;
		case IDM_FACE_RIGHTC://提取右脸颊
			OnFaceExtraShow();//脸部分割
			break;
		case IDM_FACE_NOSE://提取鼻子
			OnFaceExtraShow();//脸部分割
			break;
		case IDM_FACE_BOTTOM ://提取下巴
			OnFaceExtraShow();//脸部分割
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
	m_choice = IDM_DSCRETCH;
	PPieceGray dlg;
	dlg.setDlgTitle("对比度拉伸",IDM_DSCRETCH);
	dlg.DoModal();
	OnMenu();
}

void CPImageApp::OnLayer()//灰度级分层
{
	m_choice = IDM_LAYER;
	CFFilterDlg dlg;
	dlg.setDlgTitle("灰度级分层",IDM_LAYER);
	dlg.DoModal();
	OnMenu();
}

void CPImageApp::OnBitLayer()//比特层面分层
{
	m_choice = IDM_BIT_LAYER;
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
				m_savePic[i] = m_mat[i];
				MatToCImage(m_mat[i],m_img[i]);
				
			}
			m_last_recoverNum = m_recoverNum;
			cimageview->setImg(m_img,m_choice);
		}
		else
		{
			m_savePics = mat;
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

	if(m_odk)
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
		return iDft[0];
		//ShowImage(iDft[0]);
		//imwrite(_T("C:/Users/Administrator/Desktop/图像处理/lena_big.png"),iDft[0]);
		//imwrite(_T("C:\\sample1024.bmp"),iDft[0]);
		//imshow("view", iDft[0]);
	}
	return magI;
	
	//ShowImage(magI);
}

void CPImageApp::getHis(int sum, int * intensity)
{
	m_hsum = sum;
	m_intensity = intensity;
}

int CPImageApp::foundThreshold(int rows, int cols, float T,  Mat mat, float T0 )
{
	//全局阈值处理
	
	float low_nums = 0,high_nums =0,low_sum=0, hig_sum =0,low_ave =0,high_ave =0;
	for (int i = 0; i < rows; i++)
	{
		uchar *srcData = mat.ptr<uchar>(i);
		for (int j = 0; j < cols; j++)
		{
			if(srcData[j] <= T)
			{
				low_nums++;
				low_sum += srcData[j];
				//dstMat.at<uchar>(i, j) = 255;
			}		
			else
			{
				high_nums++;
				hig_sum += srcData[j];
				//dstMat.at<uchar>(i, j) = 255;

			}
		}
	}
	if(low_nums==0)
	{
		low_nums++;
	}
	low_ave = low_sum/low_nums;
	high_ave = hig_sum/high_nums;
	float ave = (low_ave+high_ave)/2;
	//float A = ave;
	if(abs(ave-T)>2)
	{
		T = ave;
		T0 = foundThreshold(rows, cols, ave, mat,T0 );
	}
	else
	{
		return ave;
	}
	return T0;
}
LinkStack push(LinkStack &top,Point& point,int data, int tag)
{
	//利用栈来存储弹出数据
	LinkStack p = new stacknode;
	if(p != NULL)
	{
		p->point = point;
		p ->data = data;//可以理解为在链表尾部插入一个节点。
		p->tag = tag;
		p->next = top->next;//首先将 top的下一个结点接住
		top->next= p;//再进行连接 top一直在顶部
		top->length++;
	}
	else 
		cout << "没有内存可分配" << endl;
	return top;
}
//出栈函数
LinkStack pop(LinkStack &top,Point& point,int& data, int& tag)
{
	LinkStack temp = new stacknode;
	if(top->next == NULL)
		cout << "该栈为空！" << endl;
	else 
	{
		temp = top ->next;//可以理解为删除一个节点
		point = temp->point;
		data = temp ->data;
		tag = temp->tag;
		top ->next = temp ->next;
		top->length--;
		delete(temp);
	}
	return top;
}


void CPImageApp::splitFiled(Mat mat, int mfield,LinkStack &field,Point begin,Point end)
{
	if(mat.empty())
	{
		return;
	}
	//右上边区域
	int rightF = (end.y-begin.y)/2-1;
	Point rP(begin.x,rightF);
	//左下边区域
	int leftF = (end.x-begin.x)/2-1;
	Point lP(leftF,rightF);
	int beginGray = mat.at<uchar>(begin);
	int rGray = mat.at<uchar>(rP);
	int lGray = mat.at<uchar>(lP);
	int endGray = mat.at<uchar>(end);
	int tag = 0;

	
	push(field,begin,beginGray,tag);//
	push(field,rP,rGray,tag);//
	push(field,lP,lGray,tag);//
	push(field,rP,beginGray,tag);//
}

void CPImageApp::OnFieldSpoShow()//区域分裂与聚合
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

	//初始大块区域栈
	LinkStack field = new stacknode();//区域栈
	field ->next = NULL;
	field->length = 0;
	Point begin(0,0);
	Point end(nRows,nCols);
	splitFiled(gray_img,4,field,begin,end);

	Point point;
	int data = 0;
	int f_tag = 0;
	for(int i=0;i<field->length; i++)
	{
		pop(field,point,data,f_tag);////种子栈 出栈一个元素
	}
}


void CPImageApp::OnFieldGrowShow()//区域生长
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

	//查找最大值
    double maxVal = 0;
	double minVal = 0;
	Point minloc;
	Point maxloc;
	cv::minMaxLoc(gray_img, &minVal, &maxVal,&minloc,&maxloc);

	//初始加入种子栈
	LinkStack seed = new stacknode();//种子栈
	seed ->next = NULL;
	seed->length = 0;
	int seed_tag=0;
	seed = push(seed,minloc,minVal,0);//最小值的tag 0 入栈时以灰度值作为tag
	seed = push(seed,maxloc,maxVal,255);//最大值的tag 1
	
	
	Point point;
	int data = 0;
	//LinkStack seedA = pop(seed,point,data,pop_tag);//出栈一个元素
	//pop(seed,point,data,seed_tag);////种子栈 出栈一个元素
	
	LinkStack edge = new stacknode();//边框栈
	edge ->next = NULL;
	edge->length = 0;
	int edge_tag = 200;
	LinkStack s_seed = new stacknode();//小种子 分类种子栈
	Point s_point;
	s_seed ->next = NULL;
	s_seed->length = 0;
	int s_data = 0;
	int sseed_tag = 0;

	//动态数组
	int **logArr=new int *[nRows];//用于标记像素有没有被处理过
	for (int i = 0; i < nRows; i++)
	{
		logArr[i]= new int[nCols];//为每行分配空间（每行中有col个元素）
		for(int j =0;j<nCols;j++)
		{
			logArr[i][j] = 0;//将全图都标记为没处理过的像素
		}
		
	}

	int x =0, y =0;
	float c = theApp.m_text[0];
	//int threshold =  c;
	int threshold =  maxVal*c;
	for(int i = 0; i<=seed->length; i++)//种子栈
	{
		pop(seed,point,data,seed_tag);////种子栈 出栈一个元素
		push(s_seed,point,data,seed_tag);////小种子栈 入栈一个元素
		for(int j = 0; j<s_seed->length ; j++)
		{
			pop(s_seed,s_point,s_data,sseed_tag);////小种子栈 出栈一个元素
			//在这个种子的周围进行运动
			x = s_point.x;
			y = s_point.y;
		
			if((x-1)<0|| (x+1)>=nRows || (y-1) < 0 || (y+1)>=nCols)//边框入栈
			{
				int gray = gray_img.at<uchar>(x, y);
				Point p(x,y);
				push(edge,p,gray,edge_tag);
				logArr[x][y] = 0;
			}
			else 
			{
				int pos = gray_img.at<uchar>(x, y);
				if(pos != s_data)
				{
					sseed_tag = 255;
					//sseed_tag = 0;
					//sseed_tag = pos ;
					//sseed_tag = s_data ;
				}
				int pos_top = gray_img.at<uchar>(x-1, y);
				int pos_bott = gray_img.at<uchar>(x+1, y);
				int pos_left = gray_img.at<uchar>(x, y-1);
				int pos_right = gray_img.at<uchar>(x, y+1);
				int pos_lt = gray_img.at<uchar>(x-1, y-1);
				int pos_lb = gray_img.at<uchar>(x+1, y-1);
				int pos_rt = gray_img.at<uchar>(x-1, y+1);
				int pos_rb = gray_img.at<uchar>(x+1, y+1);
				s_point.x = x-1;
				s_point.y = y-1;
				s_data = pos_lt;
				logArr[x][y] = 1;
				if(abs(pos-pos_lt)<threshold && logArr[x-1][y-1]==0)//左上
				{
					push(s_seed,s_point,s_data,sseed_tag);////小种子栈 入栈一个元素
					logArr[x-1][y-1]=1;//标记使用过
					dstMat.at<uchar>(x-1, y-1) = sseed_tag;
				}
				else if(abs(pos-pos_lt)>=threshold && logArr[x-1][y-1]==0)
				{
					push(seed,s_point,s_data,255);////种子栈 入栈一个元素
					//push(seed,s_point,s_data,s_data);////种子栈 入栈一个元素
				}
				 if(logArr[x-1][y-1]==1)
				 {
					 cout<<"";
				 }
				s_point.x = x-1;
				s_point.y = y;
				s_data = pos_top;
				if(abs(pos-pos_top)<threshold && logArr[x-1][y]==0)//上
				{
					push(s_seed,s_point,s_data,sseed_tag);////小种子栈 入栈一个元素
					logArr[x-1][y-1]=1;//标记使用过
					dstMat.at<uchar>(x-1, y) = sseed_tag;
				}
				else if(abs(pos-pos_top)>=threshold && logArr[x-1][y]==0)
				{
					push(seed,s_point,s_data,255);////种子栈 入栈一个元素
					//push(seed,s_point,s_data,s_data);////种子栈 入栈一个元素
				}
				s_point.x = x-1;
				s_point.y = y+1;
				s_data = pos_rt;
				if(abs(pos-pos_rt)<threshold && logArr[x-1][y+1]==0)//右上
				{
					
					push(s_seed,s_point,s_data,sseed_tag);////小种子栈 入栈一个元素
					logArr[x-1][y+1]=1;//标记使用过
					dstMat.at<uchar>(x-1, y+1) = sseed_tag;
				}
				else if(abs(pos-pos_rt)>=threshold&& logArr[x-1][y+1]==0)
				{
					push(seed,s_point,s_data,255);////种子栈 入栈一个元素
					//push(seed,s_point,s_data,s_data);////种子栈 入栈一个元素
				}
				s_point.x = x;
				s_point.y = y-1;
				s_data = pos_left;
				if(abs(pos-pos_left)<threshold && logArr[x][y-1]==0)//左
				{
					
					push(s_seed,s_point,s_data,sseed_tag);////小种子栈 入栈一个元素
					logArr[x][y-1]=1;//标记使用过
					dstMat.at<uchar>(x, y-1) = sseed_tag;
				}
				else if(abs(pos-pos_left)>=threshold && logArr[x][y-1]==0)
				{
					push(seed,s_point,s_data,255);////种子栈 入栈一个元素
					//push(seed,s_point,s_data,s_data);////种子栈 入栈一个元素
				}
				s_point.x = x;
				s_point.y = y+1;
				s_data = pos_right;
				if(abs(pos-pos_right)<threshold && logArr[x][y+1]==0)//右
				{
					
					push(s_seed,s_point,s_data,sseed_tag);////小种子栈 入栈一个元素
					logArr[x][y+1]=1;//标记使用过
					dstMat.at<uchar>(x, y+1) = sseed_tag;
				}
				else if(abs(pos-pos_right)>=threshold && logArr[x][y+1]==0)
				{
					push(seed,s_point,s_data,255);////种子栈 入栈一个元素
					//push(seed,s_point,s_data,s_data);////种子栈 入栈一个元素
				}
				s_point.x = x+1;
				s_point.y = y-1;
				s_data = pos_lb;
				if(abs(pos-pos_lb)<threshold && logArr[x+1][y-1]==0)//左下
				{
					
					push(s_seed,s_point,s_data,sseed_tag);////小种子栈 入栈一个元素
					logArr[x+1][y-1]=1;//标记使用过
					dstMat.at<uchar>(x+1, y-1) = sseed_tag;
				}
				else if(abs(pos-pos_lb)>=threshold&& logArr[x+1][y-1]==0)
				{
					push(seed,s_point,s_data,255);////种子栈 入栈一个元素
					//push(seed,s_point,s_data,s_data);////种子栈 入栈一个元素
				}
				s_point.x = x+1;
				s_point.y = y;
				s_data = pos_bott;
				if(abs(pos-pos_bott)<threshold && logArr[x+1][y]==0)//下
				{
					
					push(s_seed,s_point,s_data,sseed_tag);////小种子栈 入栈一个元素
					logArr[x+1][y]=1;//标记使用过
					dstMat.at<uchar>(x+1, y) = sseed_tag;
				}
				else if(abs(pos-pos_bott)>=threshold && logArr[x+1][y]==0)
				{
					push(seed,s_point,s_data,255);////种子栈 入栈一个元素
					//push(seed,s_point,s_data,s_data);////种子栈 入栈一个元素
				}
				s_point.x = x+1;
				s_point.y = y+1;
				s_data = pos_rb;
				if(abs(pos-pos_rb)<threshold && logArr[x+1][y+1]==0)//右下
				{
					
					push(s_seed,s_point,s_data,sseed_tag);////小种子栈 入栈一个元素
					logArr[x+1][y+1]=1;//标记使用过
					dstMat.at<uchar>(x+1, y+1) = sseed_tag;
				}
				else if(abs(pos-pos_rb)>=threshold &&logArr[x+1][y+1]==0)
				{
					push(seed,s_point,s_data,255);////种子栈 入栈一个元素
					//push(seed,s_point,s_data,s_data);////种子栈 入栈一个元素
				}
			}
		}
		
	}
	/*
	int a[500][500];
	for (int i = 0; i < nRows; i++)
	{
		for(int j =0;j<nCols;j++)
		{
			a[i][j] = logArr[i][j];//将全图都标记为没处理过的像素
		}
		
	}*/
	ShowImage(dstMat);
	//m_last_filter =  m_choice;
	//m_filterMat = dstMat;//保存高通滤波后的图，用于人脸分割
	//onFaceCutShow(dstMat);//进行人脸分割
}

void CPImageApp::OnEdgeCannyShow() //canny算子
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

	//边缘检测
	//查找最大值
    double maxVal = 0;
	cv::minMaxLoc(dstMat, NULL, &maxVal);
	Canny(gray_img, dstMat, 30, 150);//double threshold1, double threshold2,
	if(m_choice == IDM_EDGE_CANNY)//canny算子
	{
		m_mat[0] = dstMat;
		m_recoverNum = 1;
		ShowImage(dstMat);
		m_filterMat = dstMat;//保存高通滤波后的图，用于人脸分割
	}

    //灰度化
	Mat houghMat;
	Mat midMat = dstMat.clone();
    cvtColor(midMat, houghMat, CV_GRAY2BGR);
	vector<Vec4i> lines;
    //与HoughLines不同的是，HoughLinesP得到lines的是含有直线上点的坐标的，所以下面进行划线时就不再需要自己求出两个点来确定唯一的直线了
    HoughLinesP(midMat, lines, 1, CV_PI / 180, maxVal*0.01);//注意第五个参数，为阈值

    //依次画出每条线段
    for (size_t i = 0; i < lines.size(); i++)
    {
        Vec4i l = lines[i];

        line(houghMat, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255)); //Scalar函数用于调节线段颜色
	}
	/*
    // 定义矢量结构存放检测出来的直线
    vector<Vec2f> lines;
    //通过这个函数，我们就可以得到检测出来的直线集合了
    HoughLines(midMat, lines, 1, CV_PI / 180, 50, 0, 0);
    //这里注意第五个参数，表示阈值，阈值越大，表明检测的越精准，速度越快，得到的直线越少（得到的直线都是很有把握的直线）
    //这里得到的lines是包含rho和theta的，而不包括直线上的点，所以下面需要根据得到的rho和theta来建立一条直线

    //依次画出每条线段
    for (size_t i = 0; i < lines.size(); i++)
    {
        float rho = lines[i][0]; //就是圆的半径r
        float theta = lines[i][1]; //就是直线的角度
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000 * (a));

        line(houghMat, pt1, pt2, Scalar(55, 100, 195)); //Scalar函数用于调节线段颜色，就是你想检测到的线段显示的是什么颜色

    }*/
	if(m_choice == IDM_EDGE_HOUGH)//霍夫变换
	{
		m_mat[0] = dstMat;
		m_mat[1] = houghMat;
		m_recoverNum = 2;
		ShowImage(houghMat);
		m_filterMat = houghMat;//保存高通滤波后的图，用于人脸分割
	}
	m_last_filter =  m_choice;
	//onFaceCutShow(dstMat);//进行人脸分割
	
}

void CPImageApp::OnEdgeDetectShow() //基于边缘检测
{
}

void CPImageApp::OnThresholdShow()//阈值处理
{
	m_recover = true;
	//基本全局阈值
	Mat imat = ReadImage();
	// 输入图像判断
    if (imat.empty())
        return;
	int chanels = imat.channels();
	Mat gray_img,dstMat;
	
	RGBtoGRAY(imat,gray_img);//RGB转换GRAY
	/*
	if(!m_filterMat.empty())
	{
		gray_img = m_filterMat.clone();
	}*/
	dstMat = gray_img.clone();
	int nRows = dstMat.rows;
	int nCols = dstMat.cols;
	//int T0 = theApp.m_text[0];//估计的阈值
	float T0 = 0.0;
	float T = foundThreshold(nRows, nCols, 0.0, gray_img,T0 );

	/*
	//查找最大值
    double maxVal = 0;
	double minVal = 0;
	Point minloc;
	Point maxloc;
	cv::minMaxLoc(gray_img, &minVal, &maxVal);
	T=maxVal-(maxVal-minVal)/2;
	*/

	for (int i = 0; i < nRows; i++)
	{
		uchar *srcData = gray_img.ptr<uchar>(i);
		for (int j = 0; j < nCols; j++)
		{
			if(srcData[j] > T)
			{
				dstMat.at<uchar>(i, j) = 255;
			}		
			else
			{
				dstMat.at<uchar>(i, j) = 0;
			}
		}
	}

	if(m_choice == IDM_GLOBAL_THRESHOLD)//基本全局阈值处理
	{
		m_mat[0] = dstMat;
		m_recoverNum = 1;
		ShowImage(dstMat);
		//m_filterMat = dstMat;//保存高通滤波后的图，用于人脸分割
		//m_last_filter = IDM_GLOBAL_THRESHOLD;
	}

	//最大类间方差法 OTSU
	Histogram1D hist;
    Mat histMat = hist.getHistogramImage(gray_img,m_choice);//原图

	//取k = T;将各个像素基于灰度分成两类 C0，C1
	float p[256];
	float sum=0;
	float w0 = 0, w1 =0;//概率和
	float sump0 = 0, sump1 =0;//总的灰度值
	float u0 =0, u1 =0;//平均灰度值
	for(int i =0; i<256; i++)
	{
		p[i] = (float)theApp.m_intensity[i]/(float)theApp.m_hsum;
		sum +=p[i];

		if(i<T)
		{
			w0 += p[i];//C0区域的总概率
			sump0 += i*p[i]; 
		}
		else
		{
			w1 += p[i];//C1区域的总概率
			sump1 += i*p[i];
		}
	}
	
	u0 = sump0/w0;//C0区域的平均灰度值
	u1 = sump1/w1;//C1区域的平均灰度值
	float u =0;//总的平均灰度值
	u= w0*u0 + w1*u1;//总的平均灰度值  u= sump0 + sump1;
	float omg = 0;
	//omg = w0 * (u0-u)*(u0-u) + w1 * (u1-u)*(u1-u);
	float max =0; 
	int max_num =1;//用于计算最大值的个数
	int maxh[100];//用于记录相同最大值的灰度值
	for(int i = 0; i<256; i++)
	{
		
		for(int j =0; j<256; j++)
		{
			p[j] = (float)theApp.m_intensity[j]/(float)theApp.m_hsum;
			if(j<i)
			{
				w0 += p[j];//C0区域的总概率
				sump0 += j*p[j]; 
			}
			else
			{
				w1 += p[j];//C1区域的总概率
				sump1 += j*p[j];
			}
		}
		u0 = sump0/w0;//C0区域的平均灰度值
		u1 = sump1/w1;//C1区域的平均灰度值
		omg = w0 * (u0-u)*(u0-u) + w1 * (u1-u)*(u1-u);
		if(omg>max)
		{
			max = omg;
			max_num=1;
			maxh[0]= i;//将当前的灰度值赋值
		}
		else if(max == omg)
		{
			maxh[max_num] = i;
			max_num ++;
		}
	}
	int sumT =0;
	for(int i =0;i<max_num;i++)
	{
		sumT += maxh[i];
	}
	T = sumT/max_num;

	Mat otsuMat = gray_img.clone();

	int rows = otsuMat.rows;
	int cols = otsuMat.cols;
	for (int i = 0; i < rows; i++)
	{
		uchar *srcData = gray_img.ptr<uchar>(i);
		for (int j = 0; j < cols; j++)
		{
			if(srcData[j] > T)
			{
				otsuMat.at<uchar>(i, j) = 255;
			}
			
			else
			{
				otsuMat.at<uchar>(i, j) = 0;
			}
		}
	}
	if(m_choice == IDM_OTSU_THRESHOLD)//otsu阈值处理
	{
		m_mat[0] = dstMat;
		m_mat[1] = otsuMat;
		m_recoverNum = 2;
		
		ShowImage(otsuMat);
		//m_filterMat = otsuMat;//保存高通滤波后的图，用于人脸分割
		//m_last_filter = IDM_OTSU_THRESHOLD;
	}
	
	//onFaceCutShow(dstMat);//进行人脸分割
	//imshow("33",otsuMat);
	//
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
	

	
	//向右模糊六点
	Mat dst = Mat::zeros(nRows,nCols, CV_8U);
	int m,temp;
	int n=6;
	double average=0;
	for(int i = 0; i < nRows; i++)
	{   
		for(int j = 0; j < nCols; j++)
		{ 
			temp=nCols-j;
			if (temp<n)
			{
				n=temp;
			}
			for(m = 0; m < n; m++)
			{
				average+=dstMat.at<uchar>(i, j+m);
			}	
			if(i == 210 && j == 154)
			{
				int w = 0;
			}
			
			dst.at<uchar>(i, j)=(unsigned char)(average/n+0.5);
			double a = dst.at<uchar>(i, j); // 模糊值
			double b = dstMat.at<uchar>(i, j);  //原图值
			average=0;
			m=0;
		} 
		n=6;
	}
	//imshow("",dst);
	if(m_choice == IDM_WHITE)
	{
		m_mat[0] = dstMat;
		m_mat[1] = dst;
		m_recoverNum = 2;
		ShowImage(dst);//白线
	}
	
	//imwrite(_T("C:/Users/Administrator/Desktop/图像处理/mohu.bmp"),dst);
	
	//截取图像
	Mat cutsrcMat = dstMat.clone();
	Mat cutdstMat = dst.clone();
	int WinHeight = 16;
	int WinWidth = 16;
	int starti = pos_x-(WinHeight/2-1);
	int startj = pos_y-(WinWidth/2-1);
	int endi = starti+WinHeight;
	int endj = startj+WinWidth;

	
	for(int i = 0; i < nRows; i++)
	{   
		for(int j = 0; j < nCols; j++)
		{ 
			if(i>=starti&&i<endi && j>=startj&&j<endj)
			{
				cutsrcMat.at<uchar>(i, j)=dstMat.at<uchar>(i, j);
				cutdstMat.at<uchar>(i, j)=dst.at<uchar>(i, j);
			}
			else
			{
				cutsrcMat.at<uchar>(i, j)= 0;
				cutdstMat.at<uchar>(i, j)= 0;
			}
		}
	}

	if(m_choice == IDM_SCRESHOT)
	{
		m_mat[0] = dstMat;
		m_mat[1] = dst;
		m_mat[2] = cutsrcMat;
		m_mat[3] = cutdstMat;
		m_recoverNum = 4;

		ShowImage(cutdstMat);//截取图像
	}

	
	//求得退化函数--小区域
	//小区域模糊图和复原图进行fft变换
	//m_odk = true;
	m_odk = true;
	Mat srcfftMat = OnFFT(cutsrcMat);
	Mat dstfftMat = OnFFT(cutdstMat);
	srcfftMat.convertTo(srcfftMat,CV_32FC1); //将图像转换为flaot型	 原图
	dstfftMat.convertTo(dstfftMat,CV_32FC1); //将图像转换为flaot型   退化图
	Mat shMat = dstfftMat/srcfftMat; //退化函数
	Mat hfMat =  shMat.clone();

	/*
	for(int i = 0; i<hfMat.rows; i++)
	{
		for(int j =0 ; j<hfMat.cols; j++)
		{
			float va = hfMat.at<float>(i, j);
			if(va==0)
			{
				hfMat.at<float>(i, j) = 1; 
			}
		}
	}*/
	
	m_reverseFMat = hfMat.clone();
	OnIlpfShow();//频域理想滤波器
	//OnBlpfShow();//频域巴特沃斯低通滤波器//对退化函数进行处理 避免噪声对其影响
	Mat hiMat = m_reverseFMat.clone();//低通滤波后的退化函数
	

	Mat smohuMat = dst.clone();//六点模糊的图
	
	//Mat oriMat  = gray_img.clone();//原图
	//oriMat.convertTo(oriMat,CV_32FC1); //将图像转换为flaot型	 原图
	//mohuMat.convertTo(mohuMat,CV_32FC1); //将图像转换为flaot型   退化图
	//Mat hbMat = mohuMat/oriMat; //退化函数
	//Mat srcoriMat = OnFFT(gray_img);//原图
	Mat sdstmhMat = OnFFT(smohuMat);//模糊图
	Mat shfiMat = OnFFT(hiMat);//模糊图
	//srcoriMat.convertTo(srcoriMat,CV_32FC1); //将图像转换为flaot型	 原图
	sdstmhMat.convertTo(sdstmhMat,CV_32FC1); //将图像转换为flaot型   退化图
	shfiMat.convertTo(shfiMat,CV_32FC1); //将图像转换为flaot型   退化图
	Mat srecMat = sdstmhMat/shfiMat; //退化函数
	//imshow("函数",hbMat);
	
	Mat srecoMat = OnFFT(srecMat);


	if(m_choice == IDM_FRESTORE)
	{
		m_mat[0] = dstMat;
		m_mat[1] = dst;
		m_mat[2] = cutsrcMat;
		m_mat[3] = cutdstMat;
		m_mat[4] = srecoMat;
		m_recoverNum = 5;
		ShowImage(srecoMat);//截取图像
	}

	

		m_odk = true;
		Mat oriMat  = dstMat.clone();//打完亮点的图
		Mat mohuMat  = dst.clone();//模糊的图
		Mat orifftMat = OnFFT(oriMat);
		Mat mohufftMat = OnFFT(mohuMat);
		orifftMat.convertTo(orifftMat,CV_32FC1); //将图像转换为flaot型	 原图
		mohufftMat.convertTo(mohufftMat,CV_32FC1); //将图像转换为flaot型   退化图
		Mat hMat = mohufftMat/orifftMat; //退化函数
		Mat thMat =  hMat.clone();

		
		m_reverseFMat = thMat.clone();
		OnIlpfShow();//频域理想滤波器
		//OnBlpfShow();//频域巴特沃斯低通滤波器//对退化函数进行处理 避免噪声对其影响
		Mat tuihuaMat = m_reverseFMat.clone();//低通滤波后的退化函数
		
		Mat mhMat = dst.clone();//六点模糊的图
		Mat dstmhMat = OnFFT(mhMat);//模糊图
		Mat hfiMat = OnFFT(tuihuaMat);//模糊图

		dstmhMat.convertTo(dstmhMat,CV_32FC1); //将图像转换为flaot型   退化图
		hfiMat.convertTo(hfiMat,CV_32FC1); //将图像转换为flaot型   退化图
		Mat recMat = dstmhMat/hfiMat; //退化函数
		//imshow("函数",hbMat);
	
		Mat recoMat = OnFFT(recMat);
		//cv::imshow("er",recoMat);
	if(m_choice == IDM_REVERFILTER)
	{
		m_mat[0] = dstMat;
		m_mat[1] = dst;
		m_mat[2] = recoMat;
		m_mat[3] = cutsrcMat;
		m_mat[4] = cutdstMat;
		m_mat[5] = srecoMat;
		
		//m_mat[5] = recoMat;
		m_recoverNum = 6;

		ShowImage(recoMat);//截取图像
	}
		//
	//oriMat.convertTo(oriMat,CV_32FC1); //将图像转换为flaot型	 原图
	//mohuMat.convertTo(mohuMat,CV_32FC1); //将图像转换为flaot型   退化图
	//Mat hbMat = mohuMat/oriMat; //退化函数
	//Mat srcoriMat = OnFFT(gray_img);//原图
	
	/*
	m_reverseFMat = recoMat.clone();
	OnIlpfShow();//频域理想滤波器
	//OnBlpfShow();//频域巴特沃斯低通滤波器//对退化函数进行处理 避免噪声对其影响
	Mat aMat = m_reverseFMat.clone();//低通滤波后的退化函数
	cv::imshow("ttet",aMat);
	}
	//hbMat = OnFFT(hbMat);
	//m_reverseFMat = hbMat.clone();
	//OnIlpfShow();//频域理想滤波器
	//OnBlpfShow();//频域巴特沃斯低通滤波器//对退化函数进行处理 避免噪声对其影响
	//Mat hiMat = m_reverseFMat.clone();//低通滤波后的退化函数
	//imshow("退化函数",hiMat);
	
	/*
	Mat hfMat = OnFFT(hiMat);//退化函数
	Mat mhimg = dst.clone();//模糊图函数
	mhimg = OnFFT(mhimg);
	hfMat.convertTo(hfMat,CV_32FC1); //将图像转换为flaot型	 原图
	mhimg.convertTo(mhimg,CV_32FC1); //将图像转换为flaot型   退化图
	Mat recMat = mhimg/hfMat; //复原图
	imshow("er",recMat);

	
	Mat recoMat = OnFFT(recMat);
	cv::imshow("er",recoMat);
	/*
	m_odk = false;
	Mat recoMat = OnFFT(recMat);
	cv::imshow("er",recoMat);
	//Mat htMat = OnFFT(hiMat);*/

	//Mat recMat = mohuMat/hiMat;
	
	//Mat recoMat = OnFFT(recMat);
	//normalize(recoMat,recoMat,0,255,CV_MINMAX);	//归一化便于显示
	//recoMat.convertTo(recoMat,CV_8UC1); //将图像转换为flaot型
	

	/*
	Mat hMat(cutsrcMat.size(),CV_32FC1); //，CV_32FC1
	for(int p = 0; p<hMat.rows; p++)
	{
		for(int q = 0; q<hMat.cols;q++)
		{
			hMat.at<float>(p, q) = cutsrcMat.at<float>(p, q) / cutdstMat.at<float>(p, q); 
			float c= cutsrcMat.at<float>(p, q); // 模糊值
			float d= cutdstMat.at<float>(p, q);  //恢复值
			float o = hMat.at<float>(p, q);
			m_hfilter[p][q] = o;
		}
	}*/
	
	/*
	if(m_choice == IDM_RESTOREFUC)
	{
		CDegeDlg dlg;
		dlg.setDlgTitle("退化函数");
		dlg.DoModal();
		m_mat[0] = dstMat;
		m_mat[1] = dst;
		m_mat[2] = cutdstMat;
		m_mat[3] = recoMat;
		m_recoverNum = 4;

		ShowImage(recoMat);//截取图像
	}
	
	/*
	//小区域复原
	double sumvalue;//总值
	double singlevalue;//当前的值 
	//恢复点
	n = 6;
	Mat recoMat = cutdstMat.clone();
	for(int p = starti; p<endi; p++)
	{
		for(int q = endj-1; q>startj;q--)
		{
			temp=endj-q;
			if (temp<n)
			{
				n=temp;
			}
			double t= cutdstMat.at<uchar>(p, q); // 模糊值
			sumvalue = cutdstMat.at<uchar>(p, q) * n;//总值求出来
			for(int v = 1; v < n; v++)
			{
				double w = recoMat.at<uchar>(p, q+v);
				sumvalue-=recoMat.at<uchar>(p, q+v);
			}
			if(sumvalue>255)
			{
				sumvalue = 255;
			}
			singlevalue = sumvalue;
			recoMat.at<uchar>(p, q) = singlevalue;
			double a = dst.at<uchar>(p, q); // 模糊值
			double b = dstMat.at<uchar>(p, q);  //原图值
			double c= cutdstMat.at<uchar>(p, q); // 模糊值
			double d= recoMat.at<uchar>(p, q);  //恢复值
			n = 6;
		}
	}
	
	if(m_choice == IDM_FRESTORE)
	{
		m_mat[0] = dstMat;
		m_mat[1] = dst;
		m_mat[2] = cutdstMat;
		m_mat[3] = recoMat;
		m_recoverNum = 4;

		ShowImage(recoMat);//截取图像
	}
	//截图小图

	
	Mat ssrcMat(WinHeight,WinWidth,CV_8UC1); //，CV_32FC1
	Mat sdstMat(WinHeight,WinWidth,CV_8UC1); //，CV_32FC1
	int s = 0, j=0;
	for(int p = starti; p<endi; p++)
	{
		for(int q = startj; q<endj;q++)
		{
			//退化图像 小图
			ssrcMat.at<uchar>(s, j) = cutdstMat.at<uchar>(p, q); 
			//恢复图像小图
			sdstMat.at<uchar>(s, j) = recoMat.at<uchar>(p, q);
			j++;

		}
		s++;
		j = 0;
	}
	//imshow("3",ssrcMat);
	//imshow("4",sdstMat);
	
	//小区域模糊图和复原图进行fft变换
	Mat srcfftMat = OnFFT(ssrcMat);
	Mat dstfftMat = OnFFT(sdstMat);
	//imshow("5",srcfftMat);
	//imshow("6",dstfftMat);

	//求得退化函数
	srcfftMat.convertTo(srcfftMat,CV_32FC1); //将图像转换为flaot型	 退化图
	dstfftMat.convertTo(dstfftMat,CV_32FC1); //将图像转换为flaot型   恢复图

	Mat hMat(srcfftMat.size(),CV_32FC1); //，CV_32FC1
	for(int p = 0; p<hMat.rows; p++)
	{
		for(int q = 0; q<hMat.cols;q++)
		{
			hMat.at<float>(p, q) = srcfftMat.at<float>(p, q) / dstfftMat.at<float>(p, q); 
			float c= srcfftMat.at<float>(p, q); // 模糊值
			float d= dstfftMat.at<float>(p, q);  //恢复值
			float o = hMat.at<float>(p, q);
			m_hfilter[p][q] = o;
		}
	}
	//imshow("7",hMat);
	if(m_choice == IDM_RESTOREFUC)
	{
		CDegeDlg dlg;
		dlg.setDlgTitle("退化函数");
		dlg.DoModal();
		m_mat[0] = dstMat;
		m_mat[1] = dst;
		m_mat[2] = cutdstMat;
		m_mat[3] = recoMat;
		m_recoverNum = 4;

		ShowImage(recoMat);//截取图像
	}
	
	
	

	/*
	//逆滤波恢复---直接用模板计算
	//int WinHeight = 16;
	//int WinWidth = 16;
	Mat rechMat = dst.clone(); //，CV_32FC1 最终恢复图像
	Mat srcgfftMat = OnFFT(dst);//退化图像的傅里叶变换
	//srcgfftMat.convertTo(srcgfftMat,CV_32FC1); //将图像转换为float型	 退化图
	hMat.convertTo(hMat,CV_8UC1); //将图像转换为flaot型   退化函数
	//Mat hfftMat = OnFFT(hMat);//退化图像的傅里叶变换
	

	for(int p = 0; p<dst.rows; p=p+WinHeight)
	{
		for(int q = dst.cols-16; q>=0;q--)
		/*for(int q = 0; q<dst.cols; q=q+WinHeight)*/
	/*	{
			for(int k = 0;k<WinHeight; k++)
			{
				for(int l =0; l<WinWidth; l++)
				{
					float g = hMat.at<uchar>(k, l);
					if( g==0)
					{
						hMat.at<uchar>(k, l) = 1;
					}
					float r= srcgfftMat.at<uchar>(p+k, q+k);
					g=  hMat.at<uchar>(k, l);
					int v= p+k;
					int u = q+l;
					rechMat.at<uchar>(p+k, q+l) = srcgfftMat.at<uchar>(p+k, q+k)/hMat.at<uchar>(k, l);
					srcgfftMat.at<uchar>(p+k, q+k) = rechMat.at<uchar>(p+k, q+l);
					float h= rechMat.at<uchar>(p+k, q+l);
					double b = imat.at<uchar>(p+k, q+l);  //原图值
				}
			}
		}
	}
	//rechMat.convertTo(hMat,CV_8UC1); //将图像转换为flaot型   退化函数
	imshow("10",rechMat);*/
	//imwrite(_T("C:/Users/Administrator/Desktop/图像处理/rech.png"),rechMat);
	/*
	//逆滤波恢复---扩展公式计算
	//dst //模糊后的图像
	//hMat // 退化模板
	double sum;//总值
	double single;//当前的值 
	//恢复点
	n = 6;
	Mat recMat = dst.clone();
	//recMat.convertTo(recMat,CV_32FC1); //将图像转换为flaot型	 恢复图
	//dst.convertTo(dst,CV_32FC1); //将图像转换为flaot型   模糊图
	//imat.convertTo(imat,CV_32FC1); //将图像转换为flaot型   原图
	for(int p = 0; p<dst.rows; p++)
	{
		for(int q = dst.cols-1; q>=0;q--)
		{
			temp=dst.cols-q;
			if (temp<n)
			{
				n=temp;
			}
			//double t= cutMat.at<uchar>(p, q); // 模糊值
			sum = (dst.at<uchar>(p, q)-0.5) * n;//总值求出来
			int d = 0;
			for(int v = 1; v < n; v++)
			{
				//double w = cutMat.at<uchar>(p, q+v);
				sum-=recMat.at<uchar>(p, q+v);
				
				d++;
			}
			if(sum>255)
			{
				sum = 255;
			}
			else if(sum<0)
			{
				sum = 0;
			}
			single = sum;
			recMat.at<uchar>(p, q) = single;

			double a = dst.at<uchar>(p, q); // 模糊值
			double b = imat.at<uchar>(p, q);  //原图值
			double c= recMat.at<uchar>(p, q); // 恢复值

			/*
			//有趣结果
			if(abs(c-b)>abs(a-b))
			{
				recMat.at<float>(p, q) = a;
			}*//*
			n = 6;
		}
	}
	
	if(m_choice == IDM_REVERFILTER)
	{
		m_mat[0] = dstMat;
		m_mat[1] = dst;
		m_mat[2] = cutdstMat;
		m_mat[3] = recoMat;
		m_mat[4] = recMat;
		m_recoverNum = 5;

		ShowImage(recMat);//截取图像
	}*/
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
	m_recover = true;
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
	/*
	if(m_choice == IDM_GLPF)//高斯低通滤波
	{
		imshow("高斯低通滤波器",gaussianBlur);
	}
	else if(m_choice == IDM_GHPF)////高斯高通滤波
	{
		imshow("高斯高通滤波器",gaussianBlur);
	}*/
	
	dstMat = freqfilt(padded,gaussianBlur);
	dstMat(cv::Rect(0,0, gray_img.cols, gray_img.rows));

	normalize(gaussianBlur,gaussianBlur,0,255,CV_MINMAX);	//归一化便于显示
	gaussianBlur.convertTo(gaussianBlur,CV_8UC1); //将图像转换为flaot型 
	m_mat[0] = gaussianBlur;
	m_mat[1] = dstMat;
	m_recoverNum = 2;
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
	m_recover = true;
	Mat imat = ReadImage();
	// 输入图像判断
    if (imat.empty())
        return;

	if(m_choice == IDM_RESTOREFUC || m_choice ==IDM_LIGHT || m_choice == IDM_WHITE 
		|| m_choice == IDM_SCRESHOT  || m_choice == IDM_REVERFILTER)//理想低通滤波器
	{
		imat = m_reverseFMat;
		CFFilterDlg dlg;
		dlg.setDlgTitle("布特沃斯低通滤波器",IDM_BLPF);
		dlg.DoModal();
	}
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
			
			if(m_choice == IDM_BLPF||m_choice == IDM_RESTOREFUC || m_choice ==IDM_LIGHT || m_choice == IDM_WHITE 
		|| m_choice == IDM_SCRESHOT  || m_choice == IDM_REVERFILTER)//频域巴特沃斯低通滤波器
			{
				butterworth_low_pass.at<float>(i,j)=1.0 / (1 + pow(d / D0, 2 * n));
			}
			else if (m_choice == IDM_BHPF)//频域巴特沃斯高通滤波器
			{
				butterworth_low_pass.at<float>(i,j)=1.0 / (1 + pow(D0 / d, 2 * n));
			}
			
		}
	}
	/*
	string name;
	if(m_choice == IDM_BLPF)//频域巴特沃斯低通滤波器
	{
		name = "布特沃斯低通滤波器d0=" + std::to_string(sigma) + "n=" + std::to_string(n);
	}
	else if (m_choice == IDM_BHPF)//频域巴特沃斯高通滤波器
	{
		name = "布特沃斯高通滤波器d0=" + std::to_string(sigma) + "n=" + std::to_string(n);
	}
	imshow(name, butterworth_low_pass);*/

	dstMat = freqfilt(padded,butterworth_low_pass);
	dstMat(cv::Rect(0,0, gray_img.cols, gray_img.rows));

	normalize(butterworth_low_pass,butterworth_low_pass,0,255,CV_MINMAX);	//归一化便于显示
	butterworth_low_pass.convertTo(butterworth_low_pass,CV_8UC1); //将图像转换为flaot型 
	m_mat[0] = butterworth_low_pass;
	m_mat[1] = dstMat;
	m_recoverNum = 2;
	ShowImage(dstMat);
	m_reverseFMat = dstMat.clone();
}

void CPImageApp::OnIlpfShow()//频域理想低通滤波器
{
	m_recover = true;
	Mat imat = ReadImage();
	// 输入图像判断
    if (imat.empty())
        return;
	int n = 0, sigma = 0;

	if(m_choice == IDM_FRESTORE || m_choice ==IDM_REVERFILTER  || m_choice ==IDM_LIGHT
		|| m_choice ==IDM_WHITE|| m_choice ==IDM_SCRESHOT )//理想低通滤波器
	{
		imat = m_reverseFMat;
		n = 222;
		sigma = 222;
	}
	else
	{
		n = theApp.m_text[0];
		sigma = theApp.m_text[1];
	}
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
	
	
	
	float d0=sigma;//半径D0越小，模糊越大；半径D0越大，模糊越小
	for(int i=0;i<padded.rows ; i++ ){
		for(int j=0; j<padded.cols ; j++ ){
			double d = sqrt(pow((i - padded.rows/2),2) + pow((j - padded.cols/2),2));//分子,计算pow必须为float型
			if(m_choice == IDM_ILPF || m_choice == IDM_FRESTORE || m_choice ==IDM_REVERFILTER || m_choice == IDM_FRESTORE || m_choice ==IDM_REVERFILTER  || m_choice ==IDM_LIGHT
		|| m_choice ==IDM_WHITE|| m_choice ==IDM_SCRESHOT )//理想低通滤波器
			{
				if (d <= d0){
					ideal_low_pass.at<float>(i,j)=1;
				}else{
					ideal_low_pass.at<float>(i,j)=0;
				}
			}
			else if (m_choice == IDM_IHPF )//频域理想高通滤波器
			{
				if (d <= d0){
					ideal_low_pass.at<float>(i,j)=0;
				}else{
					ideal_low_pass.at<float>(i,j)=1;
				}
			}
			
		}
	}
	/*
	string name;
	if(m_choice == IDM_ILPF)//理想低通滤波器
	{
		name = "理想低通滤波器d0=" + std::to_string(sigma);
	}
	else if (m_choice == IDM_IHPF)//频域理想高通滤波器
	{
		name = "理想高通滤波器d0=" + std::to_string(sigma);
	}
	//imshow(name, ideal_low_pass);
	*/
	dstMat = freqfilt(padded,ideal_low_pass);
	dstMat(cv::Rect(0,0, gray_img.cols, gray_img.rows));
	normalize(ideal_low_pass,ideal_low_pass,0,255,CV_MINMAX);	//归一化便于显示
	ideal_low_pass.convertTo(ideal_low_pass,CV_8UC1); //将图像转换为flaot型 
	if(m_choice == IDM_ILPF || m_choice == IDM_IHPF)
	{
		
		m_mat[0] = ideal_low_pass;
		m_mat[1] = dstMat;
		m_recoverNum = 2;
		ShowImage(dstMat);
	
	}
	m_reverseFMat = dstMat;
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
/*
void CPImageApp::OnCutTagShow()//记性分割标记
{
	Mat imat = ReadImage();
	// 输入图像判断
    if (imat.empty())
        return;
	
	Mat middEdgeMat;
	Mat faceEdgeMat = imat.clone();
	RGBtoGRAY(imat,middEdgeMat);//RGB转换GRAY
	cvtColor(imat, middEdgeMat, CV_BGR2GRAY);//转化边缘检测后的图为灰度图
	GaussianBlur(middEdgeMat, middEdgeMat, Size(9, 9), 2, 2);


	vector<Vec3f> circles;//保存矢量
	HoughCircles(middEdgeMat, circles, CV_HOUGH_GRADIENT, 1.5, 10, 200, 100, 0, 0);
 
	//【5】依次在图中绘制出圆
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		//绘制圆心
		circle(imat, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//绘制圆轮廓
		circle(imat, center, radius, Scalar(155, 50, 255), 3, 8, 0);
		//Scalar(55,100,195)参数中G、B、R颜色值的数值，得到想要的颜色
	}
 
	//【6】显示效果图  
	imshow("【效果图】", imat);
}*/
Mat CPImageApp::screenShoot(Mat cutMat,Point start,Point end)//用来截取图像
{
	//截取图像
	//OnFaceEdgeShow(ALL_VH);
	Mat cutFaceMat = cutMat.clone();
	int starty = start.y; //-- y 表示行
	int startx = start.x; //-- x 表示列
	int endy = end.y;
	int endx = end.x;
	int ferows = cutFaceMat.rows;
	int fecols = cutFaceMat.cols;

	//保存图像
	int sTF_rows = abs(endy - starty);
	int sTF_cols = abs(endx - startx);
	//Mat saveTagFace(sTF_rows,sTF_cols,CV_8UC1);//阈值处理后的图
	Mat saveTagFace(sTF_rows,sTF_cols,CV_8UC1);//一般的图像文件格式使用的是 Unsigned 8bits吧，CvMat矩阵对应的参数类型就是
	//CV_8UC1，CV_8UC2，CV_8UC3。
	//（最后的1、2、3表示通道数，譬如RGB3通道就用CV_8UC3）
	cvtColor(cutFaceMat, cutFaceMat, CV_BGR2GRAY);

	//将
	int p = 0,q =0;
	for(int i = starty; i<endy; i++)
	{
		q = 0;
		for(int j = startx; j<endx; j++)
		{
			saveTagFace.at<uchar>(p, q) = cutFaceMat.at<uchar>(i, j);
			//saveTagFaceThre.at<uchar>(p, q) = dstMat.at<uchar>(i, j);
			q++;
		}
		p++;
	}
	return saveTagFace;
	//m_saveFace = saveTagFace;
	//m_saveFaceThre = saveTagFaceThre;
}


void CPImageApp::OnFaceExtraShow()//脸部分割
{
	m_recover = true;
	//提取额头
	Mat topMat = m_saveFace.clone();
	Mat topMatThre = m_saveFaceThre.clone();

	//从上面往下取点
	m_filterMat = topMatThre;
	int lr = ALL_R;
	OnFaceEdgeShow(ALL_R);
	Mat middEdgeMatar = m_filterMatar.clone();
	int ferows = middEdgeMatar.rows;
	int fecols = middEdgeMatar.cols;

//	if(m_choice == IDM_FACE_TOP)//图片分割--提取额头
	int begintY = 0;//上端---行
	int begintX = fecols/4*3;//取右边眉毛作为下手处--列
	
	int gray =0;
	int white_num = 0;
	
	while(gray!=255 && begintX>0)//&& beginbY>10) //当不等于255 时进入
	{
		begintY = begintY+1;
		if(begintY>ferows/5*2)//如果查找大于整个脸的1/3 则重新找
		{
			begintX = begintX-1;
			begintY = 0;
		}
		if(begintY<ferows/4)//如果查找大于整个脸的1/3 则重新找
		{
			begintY = begintY+5;
		}
		gray = middEdgeMatar.at<uchar>(begintX,begintY);
		//gray = middEdgeMatar.at<uchar>(begintY,begintX);
		if(gray == 255)
		{
			white_num = countWhite(middEdgeMatar,begintX,begintY);//用来计算周围的白点个数
			//white_num = countWhite(middEdgeMatar,begintY,begintX);//用来计算周围的白点个数
			if(white_num<4 )
			{
				gray = 0;
				begintY = begintY+1;
			}
		}
	}
	cvtColor(middEdgeMatar, middEdgeMatar, CV_GRAY2BGR);
	//cv::rectangle(middEdgeMatar,Point(fecols/4*3,0),Point(fecols/4*3+5,0+5),Scalar(0,255,0),1,1,0);
	//cv::rectangle(middEdgeMatar,Point(begintX-2,begintY-2),Point(begintX+2,begintY+2),Scalar(0,255,0),1,1,0);
	int top_x = begintX;//列
	int top_y = begintY;//行
	//imshow("5y6",middEdgeMatar);

	
	//提取鼻子--找到上面的点
	begintY = top_y;//上端---行
	begintX = fecols/4*3;//从中间偏右下手
	
	gray =0;
	while(gray!=255 && begintX>(fecols/4))//&& beginbY>10) //当不等于255 时进入
	{
		begintY = begintY+1;
		if(begintY>ferows/4*3)//如果查找大于整个脸的3/4 则重新找
		{
			begintX = begintX-1;
			begintY = top_y;
		}
		if(begintY<top_y + 20)//如果查找小于整个脸的1/3 则继续找
		{
			begintY = begintY+20;
		}
		gray = middEdgeMatar.at<uchar>(begintX,begintY);
		//gray = middEdgeMatar.at<uchar>(begintY,begintX);
		if(gray == 255)
		{
			white_num = countWhite(middEdgeMatar,begintX,begintY);//用来计算周围的白点个数
			//white_num = countWhite(middEdgeMatar,begintY,begintX);//用来计算周围的白点个数
			if(white_num<3 )
			{
				gray = 0;
				begintY = begintY+1;
			}
		}
	}
	//cvtColor(middEdgeMatar, middEdgeMatar, CV_GRAY2BGR);
	//cv::rectangle(middEdgeMatar,Point(fecols/4*3,top_y-2),Point(fecols/4*3+2,top_y+2),Scalar(0,255,0),1,1,0);
	//cv::rectangle(middEdgeMatar,Point(begintX-2,begintY-2),Point(begintX+2,begintY+2),Scalar(0,255,0),1,1,0);
	int nose_tx = begintX;//列
	int nose_ty = begintY;//行
	//imshow("5y6",middEdgeMatar);
	
	//提取下巴--
	begintY = ferows-1;//上端---行
	begintX = fecols/4*3;//从中间偏右下手
	//cv::rectangle(middEdgeMatar,Point(begintX-2,begintY-2),Point(begintX+2,begintY),Scalar(0,255,0),1,1,0);
	gray =0;
	while(gray!=255 && begintX>fecols/4)//&& beginbY>10) //当不等于255 时进入
	{
		begintY = begintY-1;
		if(begintY<(nose_ty + (ferows-nose_ty)/3))//如果查找大于整个脸的1/2 则重新找
		{
			begintX = begintX-1;
			begintY = ferows-1;
		}
		if(begintY>(ferows/9*8))//如果查找小于整个脸的1/9 则继续找
		{
			begintY = ferows/9*8;
		}
		gray = middEdgeMatar.at<uchar>(begintX,begintY);
		//gray = middEdgeMatar.at<uchar>(begintY,begintX);
		if(gray == 255)
		{
			white_num = countWhite(middEdgeMatar,begintX,begintY);//用来计算周围的白点个数
			//white_num = countWhite(middEdgeMatar,begintY,begintX);//用来计算周围的白点个数
			if(white_num<3 )
			{
				gray = 0;
				begintY = begintY-1;
			}
		}
	}
	//cvtColor(middEdgeMatar, middEdgeMatar, CV_GRAY2BGR);
	//cv::rectangle(middEdgeMatar,Point(fecols/4*3-2,ferows-1-2),Point(fecols/4*3+2,ferows-1),Scalar(0,255,0),1,1,0);
	//cv::rectangle(middEdgeMatar,Point(begintX-2,begintY-2),Point(begintX+2,begintY+2),Scalar(0,255,0),1,1,0);
	int bottom_x = begintX;//列
	int bottom_y = begintY;//行
	//imshow("5y6",middEdgeMatar);

	
	//鼻子下面的点--从下往上
	begintY = bottom_y;//取得到的下巴分界
	begintX = fecols/4*3;//从中间偏右下手
	
	gray =0;
	while(gray!=255 && begintX>fecols/4)//&& beginbY>10) //当不等于255 时进入
	{
		begintY = begintY-1;
		if(begintY<(nose_ty + (bottom_y-nose_ty)/3))//如果查找大于整个脸的1/3 则重新找
		{
			begintX = begintX-1;
			begintY = bottom_y;
		}
		if(begintY>(bottom_y-(bottom_y-nose_ty)/6))//如果查找小于整个脸的1/3 则继续找
		{
			begintY = bottom_y-(bottom_y-nose_ty)/6;
		}
		gray = middEdgeMatar.at<uchar>(begintX,begintY);
		//gray = middEdgeMatar.at<uchar>(begintY,begintX);
		if(gray == 255)
		{
			white_num = countWhite(middEdgeMatar,begintX,begintY);//用来计算周围的白点个数
			if(white_num<5 )
			{
				gray = 0;
				begintY = begintY-1;
			}
		}
	}
	//cvtColor(middEdgeMatar, middEdgeMatar, CV_GRAY2BGR);
	//cv::rectangle(middEdgeMatar,Point(fecols/4*3-2,bottom_y-2),Point(fecols/4*3+2,bottom_y+2),Scalar(0,255,0),1,1,0);
	//cv::rectangle(middEdgeMatar,Point(begintX-2,begintY-2),Point(begintX+2,begintY+2),Scalar(0,255,0),1,1,0);
	int nose_bx = begintX;//列
	int nose_by = begintY;//行
	//imshow("5y6",middEdgeMatar);

	
	//左眼下方的点-- 从上往下求 -- 区域为鼻子所在区域
	begintY = nose_ty;//取得到的鼻子上边界
	begintX = fecols/4;//从中间偏左入手
	
	gray =0;
	while(gray!=255 && begintX<fecols/2)//&& beginbY>10) //当不等于255 时进入
	{
		begintY = begintY+1;
		if(begintY>(nose_by -(nose_by-nose_ty)/2))//如果查找大于整个鼻子的1/2 则重新找
		{
			begintX = begintX+1;
			begintY = nose_ty;
		}
		if(begintY<nose_ty+5)//如果查找小于整个鼻子的1/10 则继续找
		{
			begintY = begintY+5;
		}
		gray = middEdgeMatar.at<uchar>(begintX,begintY);
		//gray = middEdgeMatar.at<uchar>(begintY,begintX);
		if(gray == 255)
		{
			white_num = countWhite(middEdgeMatar,begintX,begintY);//用来计算周围的白点个数
			if(white_num<4 )
			{
				gray = 0;
				begintY = begintY+1;
			}
		}
	}
	//cvtColor(middEdgeMatar, middEdgeMatar, CV_GRAY2BGR);
	//cv::rectangle(middEdgeMatar,Point(fecols/4-2,nose_ty-2),Point(fecols/4+2,nose_ty+2),Scalar(0,255,0),1,1,0);
	//cv::rectangle(middEdgeMatar,Point(begintX-2,begintY-2),Point(begintX+2,begintY+2),Scalar(0,255,0),1,1,0);
	int eye_lx = begintX;//列
	int eye_ly = begintY;//行
	//imshow("5y6",middEdgeMatar);

	/*
	//右眼下方的点-- 从上往下求 -- 区域为鼻子所在区域
	begintY = nose_ty;//取得到的鼻子上边界
	begintX = fecols/5*4;//从中间偏右入手
	
	gray =0;
	while(gray!=255 && begintX>fecols/2)//&& beginbY>10) //当不等于255 时进入
	{
		begintY = begintY+1;
		if(begintY>(nose_by -(nose_by-nose_ty)/2))//如果查找大于整个鼻子的1/2 则重新找
		{
			begintX = begintX-1;
			begintY = nose_ty;
		}
		if(begintY<nose_ty+10)//如果查找小于整个鼻子的1/10 则继续找
		{
			begintY = begintY+10;
		}
		gray = middEdgeMatar.at<uchar>(begintX,begintY);
		//gray = middEdgeMatar.at<uchar>(begintY,begintX);
		if(gray == 255)
		{
			white_num = countWhite(middEdgeMatar,begintX,begintY);//用来计算周围的白点个数
			if(white_num<3 )
			{
				gray = 0;
				begintY = begintY+1;
			}
		}
	}
	//cvtColor(middEdgeMatar, middEdgeMatar, CV_GRAY2BGR);
	cv::rectangle(middEdgeMatar,Point(fecols/5*4-2,nose_ty-2),Point(fecols/5*4+2,nose_ty+2),Scalar(0,255,0),1,1,0);
	cv::rectangle(middEdgeMatar,Point(begintX-2,begintY-2),Point(begintX+2,begintY+2),Scalar(0,255,0),1,1,0);
	int eye_rx = begintX;//列
	int eye_ry = begintY;//行
	imshow("5y6",middEdgeMatar);

	*/

	//鼻子左边的点-- 从左往右求--从下往上找 -- 区域为眼睛到鼻子所在区域  列坐标增大  行坐标减少
	begintY = nose_by;//取得到的鼻子下方的点的行坐标 -- 鼻子下边最大
	begintX = eye_lx;//从左眼的列坐标
	
	gray =0;//此时为行坐标 -- 大局移动
	int nose_mx = nose_bx>nose_tx ? nose_bx:nose_tx; //取鼻子上下两个点中最大的列坐标
	while(gray!=255 && begintY>eye_ly)//&& beginbY>10) //当不等于255 时进入 行扫描从鼻子到眼睛 -- 行坐标
	{
		begintX = begintX+1;
		if(begintX>(fecols/4*3))//如果查找大于整个鼻子 则重新找
		{
			begintY = begintY-1;
			begintX = eye_lx;
		}
		
		if(begintX<(eye_lx + abs(eye_lx-nose_mx)/5))//如果查找小于鼻子到眼睛距离的1/5
		{
			begintX = begintX+5;
		}
		gray = middEdgeMatar.at<uchar>(begintX,begintY);
		white_num = 0;
		//gray = middEdgeMatar.at<uchar>(begintY,begintX);
		if(gray == 255)
		{
			white_num = countWhite(middEdgeMatar,begintX,begintY);//用来计算周围的白点个数
			if(white_num<5 )
			{
				gray = 0;
				begintX = begintX+1;
			}
		}
	}
	//cvtColor(middEdgeMatar, middEdgeMatar, CV_GRAY2BGR);
	//cv::rectangle(middEdgeMatar,Point(eye_lx-2,nose_by-2),Point(eye_lx+2,nose_by+2),Scalar(0,255,0),1,1,0);
	//cv::rectangle(middEdgeMatar,Point(begintX-2,begintY-2),Point(begintX+2,begintY+2),Scalar(0,255,0),1,1,0);
	int nose_lx = begintX;//列
	int nose_ly = begintY;//行
	//imshow("5y6",middEdgeMatar);

	//左边脸颊的点-- 从右往左求--从下往上找 -- 区域为眼睛到鼻子左鼻翼以及下巴往上所在区域  列坐标减小  行坐标减少
	begintY = bottom_y;//取得到的下巴的点的行坐标 -- 
	begintX = nose_lx;//取得到的鼻子左翼的列坐标
	
	gray =0;//此时为行坐标 -- 大局移动
	//int nose_mx = nose_bx>nose_tx ? nose_bx:nose_tx; //取鼻子上下两个点中最大的列坐标
	while(gray!=255 && begintY>eye_ly)//&& beginbY>10) //当不等于255 时进入 行扫描从鼻子到眼睛 -- 行坐标
	{
		begintX = begintX-1;
		if(begintX<10)//如果查找大于整个鼻子 则重新找
		{
			begintY = begintY-1;
			begintX = nose_lx;
		}
		
		if(begintX>(eye_lx - abs(eye_lx-nose_mx)/5))//如果查找小于眼睛的列坐标 + 眼睛到鼻子的1/5
		{
			begintX = eye_lx - abs(eye_lx-nose_mx)/5;
		}
		gray = middEdgeMatar.at<uchar>(begintX,begintY);
		white_num = 0;
		//gray = middEdgeMatar.at<uchar>(begintY,begintX);
		if(gray == 255)
		{
			white_num = countWhite(middEdgeMatar,begintX,begintY);//用来计算周围的白点个数
			if(white_num<6 )
			{
				gray = 0;
				begintX = begintX-1;
			}
		}
	}
	//cvtColor(middEdgeMatar, middEdgeMatar, CV_GRAY2BGR);
	//cv::rectangle(middEdgeMatar,Point(nose_lx-2,bottom_y-2),Point(nose_lx+2,bottom_y+2),Scalar(0,255,0),1,1,0);
	//cv::rectangle(middEdgeMatar,Point(begintX-2,begintY-2),Point(begintX+2,begintY+2),Scalar(0,255,0),1,1,0);
	int face_lx = begintX;//列
	int face_ly = begintY;//行
	//imshow("5y6",middEdgeMatar);

//	else if(m_choice == IDM_FACE_NOSE)//图片分割--提取额头
	//{

	//}
	//头的宽度--是鼻子的上面提取点nose_tx- 左脸颊提取点宽度face_lx 的两倍
	int head_width = (nose_tx - face_lx)*2;
	//右脸颊的位置的点 左脸颊+头的宽度
	int face_rx = face_lx + head_width; //列
	int face_ry = face_ly; //行

	
	//额头图像--打框--左上点为 左脸颊的列宽（face_lx,0） 右下点为右脸颊的列宽，额头的高度-行top_ty（face_rx,top_y）
	Mat faceTopMat = topMat.clone();
	cvtColor(faceTopMat, faceTopMat, CV_GRAY2BGR);
	cv::rectangle(faceTopMat,Point(face_lx,0+5),Point(face_rx,top_y),Scalar(0,0,255),1,1,0);
	Mat fTMat = screenShoot(faceTopMat,Point(face_lx,0+5),Point(face_rx,top_y));//截取图像
	if(m_choice == IDM_FACE_TOP)//额头
	{
		m_mat[0] = faceTopMat;
		m_mat[1] = fTMat;
		m_recoverNum = 2;
		ShowImage(fTMat);//截取图像
	}
	
	//脸的宽度--是脸的右侧提取点face_rx- 脸的左侧提取点face_lx
	int face_midWidth = face_rx - face_lx;
	int face_mxModel = face_lx + face_midWidth/2; //得到脸的中间位置
	//通过判断左鼻翼与脸左右两边的距离 来判断脸部是否倾斜  按照鼻子大小为脸的1/5大小左右来衡量
	int lwidth = abs(nose_lx - face_lx);
	int rwidth = abs(nose_lx - face_rx);
	int nose_w = abs(rwidth-lwidth);
	int face_mx = face_lx + nose_w; //得到脸的中间位置
	int face_mxWidth = abs(face_mxModel - face_mx)/2;
	/*
	if(face_mx>=face_mxModel)//如果实际中心点大于假设中心点 -- 认为脸部向右倾斜
	{
		face_mxFact
	}
	else //向左倾斜
	{
		face_mx = face_mx - face_midWidth/10;
	}*/
	//鼻子左侧的距离
	//int nose_lw = abs(face_mx-nose_lx);
	//鼻子右侧的位置，脸宽的中间位置 +  到 中间位置鼻子左翼的距离
	int nose_rx = nose_lx + face_mxWidth*2; //列
	int nose_ry = nose_ly; //行
	//鼻子图像--打框--左上点为 鼻子左翼的列宽, 和鼻子上面的行高nose_ty（nose_lx,nose_ty） 
	//右下点为鼻子右翼的列宽，鼻子下方高度-行nose_by（nose_rx,nose_by）
	Mat noseMidMat = topMat.clone();
	cvtColor(noseMidMat, noseMidMat, CV_GRAY2BGR);
	cv::rectangle(noseMidMat,Point(nose_lx,nose_ty),Point(nose_rx,nose_by+(bottom_y- nose_by)/2),Scalar(0,0,255),1,1,0);
	Mat fNMat = screenShoot(noseMidMat,Point(nose_lx,nose_ty),Point(nose_rx,nose_by+(bottom_y- nose_by)/2));//截取图像
	if(m_choice == IDM_FACE_NOSE)//鼻子
	{
		m_mat[0] = noseMidMat;
		m_mat[1] = fNMat;
		m_recoverNum = 2;
		ShowImage(fNMat);//截取图像
	}

	//下巴图像--打框--左上点为 左脸颊的列宽,下巴的行高（face_lx,bottom_y） 右下点为右脸颊的列宽，图片的高度（face_rx,ferows）
	Mat faceBottomMat = topMat.clone();
	cvtColor(faceBottomMat, faceBottomMat, CV_GRAY2BGR);
	cv::rectangle(faceBottomMat,Point(face_lx + face_midWidth/5,bottom_y),Point(face_rx-face_midWidth/5,ferows-1),Scalar(0,0,255),1,1,0);
	Mat fBMat = screenShoot(faceBottomMat,Point(face_lx + face_midWidth/5,bottom_y),Point(face_rx-face_midWidth/5,ferows-1));//截取图像
	if(m_choice == IDM_FACE_BOTTOM)//下巴
	{
		m_mat[0] = faceBottomMat;
		m_mat[1] = fBMat;
		m_recoverNum = 2;
		ShowImage(fBMat);//截取图像
	}

	//左脸图像--打框--左上点为 左脸颊的列宽,眼睛的行高（face_lx,eye_ly） 右下点为鼻子左翼的的列宽，下巴的高度（nose_lx,bottom_y）
	Mat faceLeftMat = topMat.clone();
	cvtColor(faceLeftMat, faceLeftMat, CV_GRAY2BGR);
	cv::rectangle(faceLeftMat,Point(face_lx,eye_ly),Point(nose_lx,bottom_y),Scalar(0,0,255),1,1,0);
	Mat fLMat = screenShoot(faceLeftMat,Point(face_lx,eye_ly),Point(nose_lx,bottom_y));//截取图像
	if(m_choice == IDM_FACE_LEFT)//左脸
	{
		m_mat[0] = faceLeftMat;
		m_mat[1] = fLMat;
		m_recoverNum = 2;
		ShowImage(fLMat);//截取图像
	}

	//右脸图像--打框--左上点为 右鼻翼的列宽,眼睛的行高（nose_rx,eye_ly） 右下点为右脸颊的列宽，下巴的高度（face_rx,bottom_y）
	Mat faceRightMat = topMat.clone();
	cvtColor(faceRightMat, faceRightMat, CV_GRAY2BGR);
	cv::rectangle(faceRightMat,Point(nose_rx,eye_ly),Point(face_rx,bottom_y),Scalar(0,0,255),1,1,0);
	Mat fRMat = screenShoot(faceRightMat,Point(nose_rx,eye_ly),Point(face_rx,bottom_y));//截取图像
	if(m_choice == IDM_FACE_RIGHTC)//左脸
	{
		m_mat[0] = faceRightMat;
		m_mat[1] = fRMat;
		m_recoverNum = 2;
		ShowImage(fRMat);//截取图像
	}

	/*
	//截取图像
	//OnFaceEdgeShow(ALL_VH);
	Mat cutTopMat = m_filterMatar.clone();
	int starti = 0;
	int startj = 0;
	int endi = fecols;
	int endj =  top_y;
	ferows = cutTopMat.rows;
	fecols = cutTopMat.cols;
	
	
	for(int i = 0; i < ferows; i++)//此处i 是行
	{   
		for(int j = 0; j < fecols; j++)//j表示列
		{ 
			if(i>=startj&&i<endj && j>=starti&&j<endi) //x表示列。y表示行 坐标轴
			{
				cutTopMat.at<uchar>(i, j)=m_filterMatar.at<uchar>(i, j);
			}
			else
			{
				cutTopMat.at<uchar>(i, j)= 0;
			}
		}
	}

	
	//if(m_choice == IDM_FACE_TOP)//图片分割
	{
		m_mat[0] = topMatThre;
		m_mat[1] = cutTopMat;
		m_mat[2] = faceTopMat;
		m_recoverNum = 3;
		ShowImage(faceTopMat);//截取图像
	}
	}
	*/

}

void CPImageApp::OnFaceEdgeShow(int lf)
{
//边界

	Mat src_blur,rb_img,rbMat;
	src_blur = m_filterMat.clone();
	//m_choice = IDM_ROBERTS;
	
	RGBtoGRAY(src_blur,rb_img);//RGB转换GRAY
	rbMat = rb_img.clone();
	int nRows = rbMat.rows;
	int nCols = rbMat.cols;

	int x1 = 0,x2 = 0,t1,t2;
	for (int i = 0; i < nRows - 1; i++){
		for (int j = 0; j < nCols - 1; j++){
			//根据公式计算
			int pixl_gray = 0;
			//if(m_choice == IDM_FACE_EDGE )//Roberts算子
			//{
					if(lf==RIGHT )//主对角线
					{
						x1 = rb_img.at<uchar>(i + 1, j + 1)- rb_img.at<uchar>(i, j);
						
					}
					else if(lf==LEFT)//反对角线
					{
						x2 = rb_img.at<uchar>(i+1, j) -rb_img.at<uchar>(i , j + 1);
					}
					else if(lf==ALL_R)
					{
						x1 = rb_img.at<uchar>(i + 1, j + 1)- rb_img.at<uchar>(i, j);
						x2 = rb_img.at<uchar>(i+1, j) -rb_img.at<uchar>(i , j + 1);
					}
					else if(lf==VERTICAL)//垂直算子
					{
						x2 = rb_img.at<uchar>(i+1 , j )-rb_img.at<uchar>(i, j);
					}
					else if(lf==HORIZON)//水平算子
					{
						x1 = rb_img.at<uchar>(i , j + 1)-rb_img.at<uchar>(i, j) ;
					}
					else if(lf==ALL_VH)//水平算子
					{
						x1 = rb_img.at<uchar>(i , j + 1)-rb_img.at<uchar>(i, j) ;
						x2 = rb_img.at<uchar>(i+1 , j )-rb_img.at<uchar>(i, j);
					}
					
		//	}
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
			rbMat.at<uchar>(i, j) = (uchar)pixl_gray;
			
		}
	}
	
	//中值滤波
	//m_choice == IDM_ROBERTS;
	Mat result = rbMat.clone();
	Mat mediMatv;
	Mat mediMath;
	Mat mediMatl;
	Mat mediMatr;
	Mat mediMata;
	Mat mediMathv;
	int ksize = 3;

	
	if(lf==RIGHT )
	{
		medianBlur(result,mediMatr,ksize);
		m_filterMatr = mediMatr;
		//imshow("rr",mediMatr);
	}
	else if(lf==LEFT)
	{
		medianBlur(result,mediMatl,ksize);
		m_filterMatl = mediMatl;
		//imshow("ll",mediMatl);
	}
	else if(lf==ALL_R)
	{
		medianBlur(result,mediMata,ksize);
		//imshow("ee",mediMata);
		m_filterMatar = mediMata;
	}
	else if(lf==VERTICAL)
	{
		medianBlur(result,mediMatv,ksize);
		m_filterMatv = mediMatv;
		//imshow("vv",mediMatv);
	}
	else if(lf==HORIZON)
	{
		medianBlur(result,mediMath,ksize);
		//imshow("hh",mediMath);
		m_filterMath = mediMath;
	}
	else if(lf==ALL_VH)//水平算子
	{
		medianBlur(result,mediMathv,ksize);
		//imshow("hh",mediMath);
		m_filterMathv = mediMathv;
	}
	
}
void CPImageApp::OnCutTagShow()//记性分割标记
{
	//Mat refineMat = m_filterMat.clone();
	//imshow("1",refineMat);
	//cv::minMaxLoc(refineMat, &minVal, &maxVal,&minloc,&maxloc);
	//查找图像2/3高度，宽度从右边开始数的第一个白点 作为链码的起点
	
	
	//m_filterMat = refineMat;
	//左右两边出发
	

	/*
	//int gray = middEdgeMat.at<uchar>(beginX,beginY);//faceEdgeMat.at<uchar>();
	//查找最大值
    double maxVal = 0;
	double minVal = 0;
	Point minloc;
	Point maxloc;
	cv::minMaxLoc(middEdgeMat, &minVal, &maxVal,&minloc,&maxloc);

	/*
	while(gray!=255 && beginX !=0) //当不等于255 时进入
	{
		//beginY = beginY-1;
		beginX = beginX-1;
		gray = middEdgeMat.at<uchar>(beginX,beginY);
		
		
	}*/

	/*
	Point begin= maxloc; 
	beginX = begin.x;
	beginY = begin.y;
	//Point begin(beginX,beginY);
	Point point;
	
	//动态数组
	int **logArr=new int *[ferows];//用于标记像素有没有被处理过
	for (int i = 0; i < ferows; i++)
	{
		logArr[i]= new int[fecols];//为每行分配空间（每行中有col个元素）
		for(int j =0;j<fecols;j++)
		{
			logArr[i][j] = 0;//将全图都标记为没处理过的像素
		}
		
	}
	//栈用来存储顺序入栈的点
	LinkStack edge = new stacknode();//种子栈
	edge ->next = NULL;
	edge->length = 0;
	int seed_tag=0;
	

	int x=beginX, y =beginY;
	//用于表示方向
	
	int right = 0;
	int rt = 1;
	int top = 2;
	int lt = 3;
	int left =4;
	int lb = 5;
	int bottom = 6;
	int rb = 7;
	int drection = top;
	int cu_gray = middEdgeMat.at<uchar>(beginX,beginY);
	
	int same_height = 0;//记录相同高度和宽度
	int same_width = 0;
	int sl_height =0;//分别用于记录上下的高度
	int sr_height =0;//
	int sl_width =0;//分别用于记录左右两边的宽度
	int sr_width =0;

	point.x = 0;
	point.y = 0;
	push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
	drection = top;//最开始规定向上开始寻找  并且将其作为指引下一个查找点的方向 记录上一个点的查找方向
	bool first = true;
	
	while( x>0 && y>0 && x<ferows-1 && y<fecols-1 &&logArr[x][y] != 99 )//当前像素点没被标记过 则继续进行查找连接起来的边框
	{
		if(first)
		{
			logArr[x][y] = 99;
			same_height = x;
			sr_width = y;
			sr_height = x;
			first = false;
		}
		/*
		if(point.x == same_height)
		{
			sl_width = y;
			sl_height = x;
		}*//*
		if(drection == top)
		{
			cu_gray = middEdgeMat.at<uchar>(x,y-1);
			if(logArr[x][y-1]==0 && cu_gray==255)//没有被访问过，而且又是白点 上
			{
				logArr[x][y-1]=1;
				drection = top;
				point.x = x;
				point.y = y-1;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				y = y-1;
				continue;
			}
			cu_gray = middEdgeMat.at<uchar>(x-1,y-1);
			if(logArr[x-1][y-1]==0 && cu_gray==255) //左上
			{
				logArr[x-1][y-1]=1;
				drection = lt;//继续向左上找
				point.x = x-1;
				point.y = y-1;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				x = x-1;
				y = y-1;
				continue;
			}
			
			cu_gray = middEdgeMat.at<uchar>(x+1,y-1);
			if(logArr[x+1][y-1]==0 && cu_gray==255) //右上
			{
				logArr[x+1][y-1]=1;
				drection = top;//继续向上找
				
				point.x = x+1;
				point.y = y-1;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				x = x+1;
				y = y-1;
				continue;
			}
			
			cu_gray = middEdgeMat.at<uchar>(x-1,y);
			if(logArr[x-1][y]==0 && cu_gray==255) //左 实在找不到才会往左边找
			{
				logArr[x-1][y]=1;
				drection = left;
				
				point.x = x-1;
				point.y = y;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				x = x-1;
				
				continue;
			}
			
			cu_gray = middEdgeMat.at<uchar>(x+1,y);
			if(logArr[x+1][y]==0 && cu_gray==255) //右 左边找不到才会往右边找
			{
				logArr[x+1][y]=1;
				drection = right;
				
				point.x = x+1;
				point.y = y;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				x = x+1;
	
				continue;
			}
			y = y-5;//一直没找到就跳跃找
			drection = top;
			continue;
		}
		else if(drection == lt)//左上
		{
			cu_gray = middEdgeMat.at<uchar>(x-1,y-1);
			if(logArr[x-1][y-1]==0 && cu_gray==255) //左上
			{
				logArr[x-1][y-1]=1;
				drection = lt;//继续向左上找
				point.x = x-1;
				point.y = y-1;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				x = x-1;
				y = y-1;
				continue;
			}
			cu_gray = middEdgeMat.at<uchar>(x,y-1);
			if(logArr[x][y-1]==0 && cu_gray==255)//没有被访问过，而且又是白点 上
			{
				logArr[x][y-1]=1;
				drection = top;
				point.x = x;
				point.y = y-1;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				y = y-1;
				continue;
			}
			cu_gray = middEdgeMat.at<uchar>(x-1,y);
			if(logArr[x-1][y]==0 && cu_gray==255) //左 实在找不到才会往左边找
			{
				logArr[x-1][y]=1;
				drection = left;
				
				point.x = x-1;
				point.y = y;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				x = x-1;
				
				continue;
			}
			x = x-5;//一直没找到就跳跃找
			y = y-5;//跳跃左上
			drection = lt;
			continue;
		}
		else if(drection == left)//左
		{
			cu_gray = middEdgeMat.at<uchar>(x-1,y);
			if(logArr[x-1][y]==0 && cu_gray==255) //左 实在找不到才会往左边找
			{
				logArr[x-1][y]=1;
				drection = left;
				
				point.x = x-1;
				point.y = y;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				x = x-1;
				
				continue;
			}
			cu_gray = middEdgeMat.at<uchar>(x-1,y+1);
			if(logArr[x-1][y+1]==0 && cu_gray==255) //左下 继续往左下找
			{
				logArr[x-1][y+1]=1;
				drection = lb;//左下
				
				point.x = x-1;
				point.y = y+1;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				
				x = x-1;
				y = y+1;
				continue;
			}
			
			cu_gray = middEdgeMat.at<uchar>(x-1,y-1);
			if(logArr[x-1][y-1]==0 && cu_gray==255) //左上
			{
				logArr[x-1][y-1]=1;
				drection = lt;//继续向左上找
				point.x = x-1;
				point.y = y-1;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				x = x-1;
				y = y-1;
				continue;
			}
			
			cu_gray = middEdgeMat.at<uchar>(x,y+1);
			if(logArr[x][y+1]==0 && cu_gray==255) //往下寻找
			{
				logArr[x][y+1]=1;
				drection = bottom;//继续向上找
				
				point.x = x;
				point.y = y+1;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				x = x;
				y = y+1;
				continue;
			}
			
			cu_gray = middEdgeMat.at<uchar>(x,y-1);
			if(logArr[x][y-1]==0 && cu_gray==255)//没有被访问过，而且又是白点 上
			{
				logArr[x][y-1]=1;
				drection = top;
				point.x = x;
				point.y = y-1;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				y = y-1;
				continue;
			}
			x = x-5;//一直没找到就跳跃找
			drection = left;
			continue;
		}
		else if(drection == lb)//左下
		{
			cu_gray = middEdgeMat.at<uchar>(x-1,y+1);
			if(logArr[x-1][y+1]==0 && cu_gray==255) //左下 继续往左下找
			{
				logArr[x-1][y+1]=1;
				drection = lb;//左下
				
				point.x = x-1;
				point.y = y+1;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				
				x = x-1;
				y = y+1;
				continue;
			}
			cu_gray = middEdgeMat.at<uchar>(x-1,y);
			if(logArr[x-1][y]==0 && cu_gray==255) //左 实在找不到才会往左边找
			{
				logArr[x-1][y]=1;
				drection = left;
				
				point.x = x-1;
				point.y = y;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				x = x-1;
				
				continue;
			}
			cu_gray = middEdgeMat.at<uchar>(x,y+1);
			if(logArr[x][y+1]==0 && cu_gray==255) //往下寻找
			{
				logArr[x][y+1]=1;
				drection = bottom;//继续向上找
				
				point.x = x;
				point.y = y+1;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				x = x;
				y = y+1;
				continue;
			}
			x = x-5;//跳跃左下找
			y = y+5;//一直没找到就跳跃找
			drection = lb;
			continue;
		}
		else if(drection == bottom)//下
		{
			cu_gray = middEdgeMat.at<uchar>(x,y+1);
			if(logArr[x][y+1]==0 && cu_gray==255) //往下寻找
			{
				logArr[x][y+1]=1;
				drection = bottom;//继续向上找
				
				point.x = x;
				point.y = y+1;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				x = x;
				y = y+1;
				continue;
			}
			cu_gray = middEdgeMat.at<uchar>(x+1,y+1);
			if(logArr[x+1][y+1]==0 && cu_gray==255) //往右下寻找
			{
				logArr[x+1][y+1]=1;
				drection = rb;//继续右下
				
				point.x = x+1;
				point.y = y+1;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				x = x+1;
				y = y+1;
				continue;
			}
			
			cu_gray = middEdgeMat.at<uchar>(x-1,y+1);
			if(logArr[x-1][y+1]==0 && cu_gray==255) //左下 继续往左下找
			{
				logArr[x-1][y+1]=1;
				drection = lb;//左下
				
				point.x = x-1;
				point.y = y+1;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				
				x = x-1;
				y = y+1;
				continue;
			}
			
			cu_gray = middEdgeMat.at<uchar>(x+1,y);
			if(logArr[x+1][y]==0 && cu_gray==255) //右 左边找不到才会往右边找
			{
				logArr[x+1][y]=1;
				drection = right;
				
				point.x = x+1;
				point.y = y;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				x = x+1;
				y = y;
				continue;
			}
			cu_gray = middEdgeMat.at<uchar>(x-1,y);
			if(logArr[x-1][y]==0 && cu_gray==255) //左 实在找不到才会往左边找
			{
				logArr[x-1][y]=1;
				drection = left;
				
				point.x = x-1;
				point.y = y;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				x = x-1;
				
				continue;
			}
			y = y+5;//一直没找到就跳跃找
			drection = bottom;
			continue;
		}
		else if(drection == rb)//继续右下
		{
			cu_gray = middEdgeMat.at<uchar>(x+1,y+1);
			if(logArr[x+1][y+1]==0 && cu_gray==255) //往右下寻找
			{
				logArr[x+1][y+1]=1;
				drection = rb;//继续右下
				
				point.x = x+1;
				point.y = y+1;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				x = x+1;
				y = y+1;
				continue;
			}
			cu_gray = middEdgeMat.at<uchar>(x,y+1);
			if(logArr[x][y+1]==0 && cu_gray==255) //往下寻找
			{
				logArr[x][y+1]=1;
				drection = bottom;//继续向上找
				
				point.x = x;
				point.y = y+1;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				x = x;
				y = y+1;
				continue;
			}
			cu_gray = middEdgeMat.at<uchar>(x+1,y);
			if(logArr[x+1][y]==0 && cu_gray==255) //右 左边找不到才会往右边找
			{
				logArr[x+1][y]=1;
				drection = right;
				
				point.x = x+1;
				point.y = y;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				x = x+1;
				y = y;
				continue;
			}
			x = x+5;//一直没找到就跳跃找
			y = y+5;
			drection = rb;
			continue;
		}
		else if(drection == right)//右边
		{
			cu_gray = middEdgeMat.at<uchar>(x+1,y);
			if(logArr[x+1][y]==0 && cu_gray==255) //右 左边找不到才会往右边找
			{
				logArr[x+1][y]=1;
				drection = right;
				
				point.x = x+1;
				point.y = y;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				x = x+1;
				y = y;
				continue;
			}
			cu_gray = middEdgeMat.at<uchar>(x+1,y-1);
			if(logArr[x+1][y-1]==0 && cu_gray==255) //右上
			{
				logArr[x+1][y-1]=1;
				drection = rt;//继续右上
				
				point.x = x+1;
				point.y = y-1;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				x = x+1;
				y = y-1;
				continue;
			}
			
			cu_gray = middEdgeMat.at<uchar>(x+1,y+1);
			if(logArr[x+1][y+1]==0 && cu_gray==255) //往右下寻找
			{
				logArr[x+1][y+1]=1;
				drection = rb;//继续右下
				
				point.x = x+1;
				point.y = y+1;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				x = x+1;
				y = y+1;
				continue;
			}
			
			cu_gray = middEdgeMat.at<uchar>(x,y-1);
			if(logArr[x][y-1]==0 && cu_gray==255)//没有被访问过，而且又是白点 上
			{
				logArr[x][y-1]=1;
				drection = top;
				point.x = x;
				point.y = y-1;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				y = y-1;
				continue;
			}
			
			cu_gray = middEdgeMat.at<uchar>(x,y+1);
			if(logArr[x][y+1]==0 && cu_gray==255) //往下寻找
			{
				logArr[x][y+1]=1;
				drection = bottom;//继续向上找
				
				point.x = x;
				point.y = y+1;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				x = x;
				y = y+1;
				continue;
			}
			x = x+5;//一直没找到就跳跃找
			drection = right;
			continue;
		}
		else if(drection == rt)//右边右上
		{
			cu_gray = middEdgeMat.at<uchar>(x+1,y-1);
			if(logArr[x+1][y-1]==0 && cu_gray==255) //右上
			{
				logArr[x+1][y-1]=1;
				drection = rt;//继续右上
				
				point.x = x+1;
				point.y = y-1;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				x = x+1;
				y = y-1;
				continue;
			}
			cu_gray = middEdgeMat.at<uchar>(x+1,y);
			if(logArr[x+1][y]==0 && cu_gray==255) //右 左边找不到才会往右边找
			{
				logArr[x+1][y]=1;
				drection = right;
				
				point.x = x+1;
				point.y = y;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				x = x+1;
				y = y;
				continue;
			}
			cu_gray = middEdgeMat.at<uchar>(x,y-1);
			if(logArr[x][y-1]==0 && cu_gray==255)//没有被访问过，而且又是白点 上
			{
				logArr[x][y-1]=1;
				drection = top;
				point.x = x;
				point.y = y-1;
				push(edge,point,drection,0);//最小值的tag 0 入栈时以灰度值作为tag
				y = y-1;
				continue;
			}
			x = x+5;
			y = y-5;//一直没找到就跳跃找
			drection = rt;
			continue;
		}
	}
	cvtColor(faceEdgeMat, faceEdgeMat, CV_GRAY2BGR);
	//int err = sr_width - sl_width ; //获得宽度
	cv::rectangle(faceEdgeMat,Point(beginX-2,beginY-2),Point(beginX+2,beginY+2),Scalar(0,255,0),1,1,0);
	
	Point popb_point,popm_point,pope_point;
	int data,tag;
	for(int i =0; i<edge->length; i+5)
	{
		pop(edge,popb_point,data,tag);
		pop(edge,popm_point,data,tag);
		pop(edge,popm_point,data,tag);
		pop(edge,popm_point,data,tag);
		pop(edge,pope_point,data,tag);
		line(faceEdgeMat, popb_point, pope_point, Scalar(0, 0, 255)); //Scalar函数用于调节线段颜色
	}
	imshow("2",faceEdgeMat);*/
}

int CPImageApp::countWhite(Mat middEdgeMatl,int beginlX,int beginlY)//用来计算周围的白点个数
{
	//beginY = beginY-1;
		
		int white_num = 0;
		int pos[8];
		
		int pos_top = middEdgeMatl.at<uchar>(beginlX, beginlY-1);
		pos[0] = pos_top;
		int pos_bott = middEdgeMatl.at<uchar>(beginlX, beginlY+1);
		pos[1] = pos_bott;
		int pos_left = middEdgeMatl.at<uchar>(beginlX-1, beginlY);
		pos[2] = pos_left;
		int pos_right = middEdgeMatl.at<uchar>(beginlX+1, beginlY);
		pos[3] = pos_right;
		int pos_lt = middEdgeMatl.at<uchar>(beginlX-1, beginlY-1);
		pos[4] = pos_lt;
		int pos_lb = middEdgeMatl.at<uchar>(beginlX-1, beginlY+1);
		pos[5] = pos_lb;
		int pos_rt = middEdgeMatl.at<uchar>(beginlX+1, beginlY-1);
		pos[6] = pos_rt;
		int pos_rb = middEdgeMatl.at<uchar>(beginlX+1, beginlY+1);
		pos[7] = pos_rb;

		for(int i= 0; i<8; i++)
		{
			if(pos[i]==255)
			{
				white_num++;
			}
		}
		return white_num;
}

void CPImageApp::onFaceCutShow()//进行人脸分割
{
	m_recover = true;
	//基本全局阈值
	Mat imat = ReadImage();
	// 输入图像判断
    if (imat.empty())
        return;

	m_filterMatf = imat.clone();//保存原图 后面标记用

	//基本全局阈值处理
	int chanels = imat.channels();
	Mat gray_img,dstMat;
	
	RGBtoGRAY(imat,gray_img);//RGB转换GRAY
	
	dstMat = gray_img.clone();
	int nRows = dstMat.rows;
	int nCols = dstMat.cols;
	//int T0 = theApp.m_text[0];//估计的阈值
	float T0 = 0.0;
	float T = foundThreshold(nRows, nCols, 0.0, gray_img,T0 );


	for (int i = 0; i < nRows; i++)
	{
		uchar *srcData = gray_img.ptr<uchar>(i);
		for (int j = 0; j < nCols; j++)
		{
			if(srcData[j] > T)
			{
				dstMat.at<uchar>(i, j) = 255;
			}		
			else
			{
				dstMat.at<uchar>(i, j) = 0;
			}
		}
	}

	if(m_choice == IDM_FACE_THRE)//基本全局阈值处理
	{
		m_mat[0] = dstMat;
		m_recoverNum = 1;
		ShowImage(dstMat);
	} 
	m_filterMat = dstMat.clone();//用于人脸分割

	//边缘检测--Roberts交叉算子--正对角线
	int lr = LEFT;
	OnFaceEdgeShow(LEFT);
	Mat middEdgeMatl = m_filterMatl.clone();
	int ferows = middEdgeMatl.rows;
	int fecols = middEdgeMatl.cols;
	int beginlX = 50;//409
	int beginlY = ferows/2;
	int gray =0;
	int white_num =0;
	//检测左脸颊  at 是在第几行第几列 i--行 j--列
	while(gray!=255 && beginlX<fecols-50) //当不等于255 时进入
	{
		beginlX = beginlX+1;
		gray = middEdgeMatl.at<uchar>(beginlX,beginlY);
		if(gray == 255) //&&white_num<4 )
		{
			white_num = 0;
			white_num = countWhite(middEdgeMatl,beginlX,beginlY);//用来计算周围的白点个数
			if(white_num<4)
			{
				gray = 0;
				if(beginlY>=ferows-2)
				{
					beginlY = ferows-10;
				}
				else if(beginlY<=1)
				{
					beginlY = 10;
				}
				else
				{
					beginlY = beginlY +1;
				}
			}
		}
	}
	cvtColor(middEdgeMatl, middEdgeMatl, CV_GRAY2BGR);


	////检测右脸颊 反对角线Roberts算子
	lr = RIGHT;
	OnFaceEdgeShow(RIGHT);
	Mat middEdgeMatr = m_filterMatr.clone();
	ferows = middEdgeMatr.rows;
	fecols = middEdgeMatr.cols;
	
	int beginrX = fecols-50;//409
	int beginrY = ferows/5*2 -6;
	gray =0;
	while(gray!=255 && beginrX>50) //当不等于255 时进入
	{
		//beginY = beginY-1;
		beginrX = beginrX-1;
		gray = middEdgeMatr.at<uchar>(beginrY,beginrX);
		
	}
	cvtColor(middEdgeMatr, middEdgeMatr, CV_GRAY2BGR);
	/*
	if(m_choice == IDM_FACE_EDGE)//Roberts算子边缘检测
	{
		m_mat[0] = dstMat;
		m_mat[1] = middEdgeMatl;
		m_mat[2] = middEdgeMatr;
		m_recoverNum = 3;
		ShowImage(middEdgeMatr);
	} */
	
	//脸部标记
	//OnFaceEdgeShow(ALL_R);
	//Mat facelrTagMat = m_filterMatar.clone();
	int fheight = abs( beginrX - beginlX);
	//int fpos = fheight/2;
	int left_x = 0, right_x =0, left_y = 0, right_y = 0;
	left_x = beginlX;
	left_y = abs(beginlY-fheight);
	right_x = beginrX;
	right_y = abs(beginrY+fheight);
	/*
	if(fheight>=fecols/3)
	{
		left_x = beginlX;
		left_y = abs(beginlY-fheight);
		right_x = beginrX;
		right_y = abs(beginrY+fheight);
		//cv::rectangle(facelrTagMat,Point(left_x,left_y),Point(right_x,right_y),Scalar(0,0,255),1,1,0);
	}
	else if(fheight<fecols/3) //如果检测到的左右两点间距太小
	{
		left_x = beginlX;
		left_y = abs(beginrY-fheight);
		right_x = beginrX;
		right_y = abs(beginrY+fheight);
		//cv::rectangle(facelrTagMat,Point(left_x,left_y),Point(right_x,right_y),Scalar(0,0,255),1,1,0);
	}*/

	//截取图像
	OnFaceEdgeShow(ALL_R);
	Mat cutlrMat = m_filterMatar.clone();
	int starti = left_x;
	int startj = left_y;
	int endi = right_x;
	int endj = right_y;
	ferows = cutlrMat.rows;
	fecols = cutlrMat.cols;
	for(int i = 0; i < ferows; i++)//此处i 是行
	{   
		for(int j = 0; j < fecols; j++)//j表示列
		{ 
			if(i>=startj&&i<endj && j>=starti&&j<endi) //x表示列。y表示行 坐标轴
			{
				cutlrMat.at<uchar>(i, j)=m_filterMatar.at<uchar>(i, j);
			}
			else
			{
				cutlrMat.at<uchar>(i, j)= 0;
			}
		}
	}
	//cvtColor(cutlrMat, cutlrMat, CV_GRAY2BGR);
	//Roberts算子后截取的图像
	if(m_choice == IDM_FACE_EDGE)//图片分割
	{
		m_mat[0] = dstMat;
		m_mat[1] = cutlrMat;
		m_recoverNum = 2;
		ShowImage(cutlrMat);//截取图像
	}

	
	////检测上端脸颊 垂直算子 检测脸部线条 比如眼睛，嘴巴 眉毛都是水平线条
	m_filterMat = cutlrMat.clone();//裁剪完的图像赋值 从下往上找
	lr = VERTICAL;
	OnFaceEdgeShow(VERTICAL);
	Mat middEdgeMatv = m_filterMatv.clone();
	ferows = middEdgeMatv.rows;
	fecols = middEdgeMatv.cols;
	
	int beginbX = starti + fheight/2;//取左右截取图像的中间
	int value = starti + fheight/2;//中间变量
	int beginbY = right_y;
	gray =0;

	while(gray!=255 && beginbX!=left_x) //&& beginbY>10) //当不等于255 时进入
	{
		beginbY = beginbY-1;
		if((beginbY-left_y)<fheight*0.8)
		{
			beginbX = beginbX +2;
			if(beginbX>=endi)
			{
				value = value -2;
				beginbX = value;
			}
			beginbY = right_y;
		}
		
		gray = middEdgeMatv.at<uchar>(beginbX,beginbY);
		if(gray == 255)
		{
			white_num = countWhite(middEdgeMatv,beginbX,beginbY);//用来计算周围的白点个数
			if(white_num<4 )
			{
				gray = 0;
				beginbY = beginbY-1;
			}
		}
	}
	cvtColor(middEdgeMatv, middEdgeMatv, CV_GRAY2BGR);
	//int err = sr_width - sl_width ; //获得宽度
	cv::rectangle(middEdgeMatv,Point(beginbX-2,beginbY-2),Point(beginbX+2,beginbY+2),Scalar(0,255,0),1,1,0);
	int bottom_x = beginbX;
	int bottom_y = beginbY;
	//imshow("5y5",middEdgeMatv);
	

	//从上面往下取点
	m_filterMat = cutlrMat;//裁剪完的图像赋值 从下往上找
	lr = HORIZON;
	OnFaceEdgeShow(HORIZON);
	Mat middEdgeMath = m_filterMath.clone();
	ferows = middEdgeMath.rows;
	fecols = middEdgeMath.cols;
	
	int begintX = starti + fheight/2;//取左右截取图像的中间
	int value_t = starti + fheight/2;//中间变量
	int begintY = left_y;//上端
	gray =0;
	while(gray!=255 && begintX!=left_x) //&& beginbY>10) //当不等于255 时进入
	{
		begintY = begintY+1;
		if((begintY-left_y)>fheight/2)
		{
			begintX = begintX-1;
			if(begintX>=endi)
			{
				value_t = value_t +1;
				begintX = value_t;
			}
			begintY = left_y;
		}
		
		gray = middEdgeMath.at<uchar>(begintX,begintY);
		if(gray == 255)
		{
			white_num = countWhite(middEdgeMath,begintX,begintY);//用来计算周围的白点个数
			if(white_num<4 )
			{
				gray = 0;
				begintY = begintY+1;
			}
		}
	}
	cvtColor(middEdgeMath, middEdgeMath, CV_GRAY2BGR);
	cv::rectangle(middEdgeMath,Point(begintX-2,begintY-2),Point(begintX+2,begintY+2),Scalar(0,255,0),1,1,0);
	int top_x = begintX;
	int top_y = begintY;
	//imshow("5y6",middEdgeMath);
	
	int height = abs(top_y - bottom_y);
	int face_tx = 0, face_ty = 0, face_bx = 0, face_by = 0;//x表示列。y表示行 坐标轴
	if(height>fheight*0.8 && height<fheight*1.2)//高度差大于宽度
	{
		face_tx = left_x;//取左边点的列数 
		face_ty = top_y-10;//取上边点的行数
		face_bx = right_x;//取右边点的列数
		face_by = bottom_y-10;//取下边点的行数
	}
	else if(height>=fheight*1.2)
	{
		int value_medi = fecols/2;
		int valueh_medi = ferows/3;
		face_tx = left_x;//取左边点的列数 
		face_bx = right_x;//取右边点的列数
		face_ty = top_y;//取上边点的行数
		face_by = bottom_y;//取下边点的行数
		if(abs(face_bx-value_medi)<abs(face_tx-value_medi)*1.5)//如果右边点离中心近，我们认为右边点在合适位置上  仅对左边点处理
		{
			face_tx = face_tx + abs(face_bx-value_medi);
		}
		else
		{
			face_bx = face_bx - abs(face_tx-value_medi)/2;
		}
		
		if(abs(face_by-valueh_medi)<abs(face_ty-valueh_medi)*1.5)//如果下边点离中心近，我们认为下边点在合适位置上  仅对上边点处理
		{
			face_ty = face_ty + abs(face_by-valueh_medi)/2;//上面处理
		}
		else
		{
			face_by = face_by - abs(face_ty-valueh_medi)*1.5;//下面处理
		}
		//face_ty = value_medi-fheight; //- fheight/5*2;//取上边点的行数
		//face_by = bottom_y+ fheight/5;//取下边点的行数*/
	}
	
	else
	{
		int value_medi = fecols/2;
		face_tx = left_x;//取左边点的列数 
		face_bx = right_x;//取右边点的列数
		if(abs(face_bx-value_medi)<abs(face_tx-value_medi))//如果右边点离中心近，我们认为右边点在合适位置上  仅对左边点处理
		{
			face_tx = face_tx + abs(face_bx-value_medi)/2;
		}
		else
		{
			face_bx = face_bx - abs(face_tx-value_medi)/2;
		}
		face_ty = top_y+ fheight/5;//取上边点的行数
		face_by = bottom_y+ fheight/7*4;//取下边点的行数
		/*
		face_tx = left_x;//取左边点的列数 
		face_bx = right_x;//取右边点的列数
		face_ty = top_y+ fheight/5;//取上边点的行数
		face_by = bottom_y+ fheight/7*4;//取下边点的行数*/
	}
	Mat faceTagMat = m_filterMatf.clone();
	cv::rectangle(faceTagMat,Point(face_tx,face_ty),Point(face_bx,face_by),Scalar(0,0,255),1,1,0);
	//imshow("sfes",faceTagMat);

	//截取图像
	OnFaceEdgeShow(ALL_VH);
	Mat cutMat = m_filterMathv.clone();
	starti = face_tx;
	startj = face_ty;
	endi = face_bx;
	endj = face_by;
	ferows = cutMat.rows;
	fecols = cutMat.cols;
	
	
	for(int i = 0; i < ferows; i++)//此处i 是行
	{   
		for(int j = 0; j < fecols; j++)//j表示列
		{ 
			if(i>=startj&&i<endj && j>=starti&&j<endi) //x表示列。y表示行 坐标轴
			{
				cutMat.at<uchar>(i, j)=m_filterMathv.at<uchar>(i, j);
				
			}
			else
			{
				cutMat.at<uchar>(i, j)= 0;
			}
		}
	}

	
	if(m_choice == IDM_FACE_FCUT)//图片分割
	{
		m_mat[0] = dstMat;
		m_mat[1] = cutlrMat;
		m_mat[2] = cutMat;
		m_recoverNum = 3;
		ShowImage(cutMat);//截取图像
	}
	
	////人脸分割--分割标记
	if(m_choice == IDM_FACE_TAG)//脸部标记
	{
		m_mat[0] = dstMat;
		m_mat[1] = cutlrMat;
		m_mat[2] = cutMat;
		m_mat[3] = faceTagMat;
		m_recoverNum = 4;
		ShowImage(faceTagMat);
	}

	//保存图像
	//Point(face_tx,face_ty),Point(face_bx,face_by);
	int sTF_rows = abs(face_ty - face_by);
	int sTF_cols = abs(face_tx - face_bx);
	Mat saveTagFaceThre(sTF_rows,sTF_cols,CV_8UC1);//阈值处理后的图
	Mat saveTagFace(sTF_rows,sTF_cols,CV_8UC1);//一般的图像文件格式使用的是 Unsigned 8bits吧，CvMat矩阵对应的参数类型就是
	//CV_8UC1，CV_8UC2，CV_8UC3。
	//（最后的1、2、3表示通道数，譬如RGB3通道就用CV_8UC3）
	cvtColor(faceTagMat, faceTagMat, CV_BGR2GRAY);

	int p = 0,q =0;
	for(int i = startj; i<endj; i++)
	{
		q = 0;
		for(int j = starti; j<endi; j++)
		{
			saveTagFace.at<uchar>(p, q) = faceTagMat.at<uchar>(i, j);
			saveTagFaceThre.at<uchar>(p, q) = dstMat.at<uchar>(i, j);
			q++;
		}
		p++;
	}
	m_saveFace = saveTagFace;
	m_saveFaceThre = saveTagFaceThre;
	//imshow("dfdsf",saveTagFace);
	//imshow("dfdsf",saveTagFaceThre);

	/*
	//脸部标记
	Mat faceTagMat = m_filterMatf.clone();
	fheight = abs( beginrX - beginlX);
	int fpos = fheight/2;
	left_x = 0; right_x =0; left_y = 0; right_y = 0;
	if(fheight>fecols/2)
	{
		left_x = beginlX;
		left_y = beginlY-fpos;
		right_x = beginrX;
		right_y = beginrY+fheight/4*3;
		cv::rectangle(faceTagMat,Point(beginlX,beginlY-fpos),Point(beginrX,beginrY+fheight/4*3),Scalar(0,0,255),1,1,0);
	}
	else
	{
		left_x = beginlX;
		left_y = beginrY-fheight;
		right_x = beginrX;
		right_y = beginrY+fpos/5*4;
		cv::rectangle(faceTagMat,Point(beginlX,beginrY-fheight),Point(beginrX,beginrY+fpos/5*4),Scalar(0,0,255),1,1,0);
	}

	

	//截取图像
	OnFaceEdgeShow(ALL_R);
	Mat cutMat = m_filterMatar.clone();
	starti = left_x;
	startj = left_y;
	endi = right_x;
	endj = right_y;
	ferows = cutMat.rows;
	fecols = cutMat.cols;
	
	for(int i = 0; i < ferows; i++)//此处i 是行
	{   
		for(int j = 0; j < fecols; j++)//j表示列
		{ 
			if(i>=startj&&i<endj && j>=starti&&j<endi) //x表示列。y表示行 坐标轴
			{
				cutMat.at<uchar>(i, j)=m_filterMatar.at<uchar>(i, j);
			}
			else
			{
				cutMat.at<uchar>(i, j)= 0;
			}
		}
	}

	
	if(m_choice == IDM_FACE_FCUT)//图片分割
	{
		m_mat[0] = dstMat;
		m_mat[1] = cutMat;
		m_recoverNum = 2;
		ShowImage(cutMat);//截取图像
	}
	
	////人脸分割--分割标记
	if(m_choice == IDM_FACE_TAG)//脸部标记
	{
		m_mat[0] = dstMat;
		m_mat[1] = cutMat;
		m_mat[2] = faceTagMat;
		m_recoverNum = 3;
		ShowImage(faceTagMat);
	}
	
	//imshow("10",faceMat);

	//OnCutTagShow();//记性分割标记
	/*
	//边界
	
	Mat src_blur,rb_img,rbMat;
	src_blur = dstMat.clone();
	m_choice = IDM_ROBERTS;
	//GaussianBlur(imat, src_blur, Size(3, 3),0, 0, BORDER_DEFAULT);
	//int chanels = imat.channels();
	RGBtoGRAY(src_blur,rb_img);//RGB转换GRAY
	rbMat = rb_img.clone();
	nRows = rbMat.rows;
	nCols = rbMat.cols;

	int x1 = 0,x2 = 0,t1,t2;
	for (int i = 0; i < nRows - 1; i++){
		for (int j = 0; j < nCols - 1; j++){
			//根据公式计算
			int pixl_gray = 0;
			if(m_choice == IDM_ROBERTS )//Roberts算子
			{
					x1 = rb_img.at<uchar>(i, j)- rb_img.at<uchar>(i + 1, j + 1);
					x2 = rb_img.at<uchar>(i+1, j) -rb_img.at<uchar>(i , j + 1);	
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
			rbMat.at<uchar>(i, j) = (uchar)pixl_gray;
			
		}
	}
	
	if(m_choice == IDM_ROBERTS)//基本全局阈值处理
	{
		m_mat[0] = dstMat;
		m_mat[1] = rbMat;
		m_recoverNum = 2;
		ShowImage(rbMat);
		
		
	} 
	*/
	/*
	//中值滤波
	m_choice = IDM_MEDIAN_FILTER;
	Mat result = rbMat.clone();
	Mat mediMat;
	int ksize = 3;
	medianBlur(result,mediMat,ksize);

	if(m_choice == IDM_MEDIAN_FILTER)//基本全局阈值处理
	{
		m_mat[0] = dstMat;
		m_mat[1] = rbMat;
		m_mat[2] =  mediMat;
		m_recoverNum = 3;
		ShowImage(mediMat);
		m_filterMat = mediMat;//保存高通滤波后的图，用于人脸分割
		//m_filterMat = dstMat;//保存高通滤波后的图，用于人脸分割
		//m_last_filter = IDM_GLOBAL_THRESHOLD;
	} 
	*/
	//m_filterMat = rbMat;//保存高通滤波后的图，用于人脸分割
	
	/*
	if(m_filterMat.empty())//保存高通滤波后的图，用于人脸分割
	{
		//默认基本全局阈值处理
		m_choice = IDM_EDGE_CANNY;
		m_last_filter == m_choice;
		OnEdgeCannyShow();//canny算子
		m_choice = IDM_FACE_CUT;
		
	}
	Mat refineMat = m_filterMat.clone();
	//if(m_last_filter != IDM_EDGE_CANNY && m_last_filter !=IDM_EDGE_HOUGH)
	//{
	//对图像进行细化处理
	//if (m_filterMat.empty()) return;//图像为空，直接返回
	
    cv::threshold(refineMat, refineMat, 128, 1, CV_THRESH_BINARY);//转为0或1的图像

    int ImgHeight = refineMat.rows;
    int ImgWidth = refineMat.cols;

	int maxIterations=-1;
    int count = 0;  //记录迭代次数
    while (true)
    {
        count++;
        if (maxIterations != -1 && count > maxIterations) //限制次数并且迭代次数到达
            break;

        vector<pair<int, int> > mFlag; //用于标记需要删除的点
        //对点标记
        for (int i = 0; i < ImgHeight; ++i)
        {
            for (int j = 0; j < ImgWidth; ++j)
            {
                //如果满足四个条件，进行标记
                //  p9 p2 p3
                //  p8 p1 p4
                //  p7 p6 p5
                int p1 = refineMat.at<uchar>(i, j);
                int p2 = (i == 0) ? 0 : refineMat.at<uchar>(i - 1, j);
                int p3 = (i == 0 || j == ImgWidth - 1) ? 0 : refineMat.at<uchar>(i - 1, j + 1);
                int p4 = (j == ImgWidth - 1) ? 0 : refineMat.at<uchar>(i, j + 1);
                int p5 = (i == ImgHeight - 1 || j == ImgWidth - 1) ? 0 : refineMat.at<uchar>(i + 1, j + 1);
                int p6 = (i == ImgHeight - 1) ? 0 : refineMat.at<uchar>(i + 1, j);
                int p7 = (i == ImgHeight - 1 || j == 0) ? 0 : refineMat.at<uchar>(i + 1, j - 1);
                int p8 = (j == 0) ? 0 : refineMat.at<uchar>(i, j - 1);
                int p9 = (i == 0 || j == 0) ? 0 : refineMat.at<uchar>(i - 1, j - 1);

                if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 2 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) <= 6)
                {
                    int ap = 0;
                    if (p2 == 0 && p3 == 1) ++ap;
                    if (p3 == 0 && p4 == 1) ++ap;
                    if (p4 == 0 && p5 == 1) ++ap;
                    if (p5 == 0 && p6 == 1) ++ap;
                    if (p6 == 0 && p7 == 1) ++ap;
                    if (p7 == 0 && p8 == 1) ++ap;
                    if (p8 == 0 && p9 == 1) ++ap;
                    if (p9 == 0 && p2 == 1) ++ap;

                    if (ap == 1)
                    {
                        if (p2*p4*p6 == 0)
                        {
                            if (p4*p6*p8 == 0)
                            {
                                //标记
                                mFlag.push_back(make_pair(i, j));
                            }
                        }
                    }
                }
            }
        }

        //将标记的点删除
        for (vector<pair<int, int> >::iterator i = mFlag.begin(); i != mFlag.end(); ++i)
        {
            refineMat.at<uchar>(i->first, i->second) = 0;
        }

        //直到没有点满足，算法结束
        if (mFlag.size() == 0) break;
        else mFlag.clear();//将mFlag清空

        //对点标记
        for (int i = 0; i < ImgHeight; ++i)
        {
            for (int j = 0; j < ImgWidth; ++j)
            {
                //如果满足四个条件，进行标记
                //  p9 p2 p3
                //  p8 p1 p4
                //  p7 p6 p5
                int p1 = refineMat.at<uchar>(i, j);
                if (p1 != 1) continue;
                int p2 = (i == 0) ? 0 : refineMat.at<uchar>(i - 1, j);
                int p3 = (i == 0 || j == ImgWidth - 1) ? 0 : refineMat.at<uchar>(i - 1, j + 1);
                int p4 = (j == ImgWidth - 1) ? 0 : refineMat.at<uchar>(i, j + 1);
                int p5 = (i == ImgHeight - 1 || j == ImgWidth - 1) ? 0 : refineMat.at<uchar>(i + 1, j + 1);
                int p6 = (i == ImgHeight - 1) ? 0 : refineMat.at<uchar>(i + 1, j);
                int p7 = (i == ImgHeight - 1 || j == 0) ? 0 : refineMat.at<uchar>(i + 1, j - 1);
                int p8 = (j == 0) ? 0 : refineMat.at<uchar>(i, j - 1);
                int p9 = (i == 0 || j == 0) ? 0 : refineMat.at<uchar>(i - 1, j - 1);

                if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 2 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) <= 6)
                {
                    int ap = 0;
                    if (p2 == 0 && p3 == 1) ++ap;
                    if (p3 == 0 && p4 == 1) ++ap;
                    if (p4 == 0 && p5 == 1) ++ap;
                    if (p5 == 0 && p6 == 1) ++ap;
                    if (p6 == 0 && p7 == 1) ++ap;
                    if (p7 == 0 && p8 == 1) ++ap;
                    if (p8 == 0 && p9 == 1) ++ap;
                    if (p9 == 0 && p2 == 1) ++ap;

                    if (ap == 1)
                    {
                        if (p2*p4*p8 == 0)
                        {
                            if (p2*p6*p8 == 0)
                            {
                                //标记
                                mFlag.push_back(make_pair(i, j));
                            }
                        }
                    }
                }
            }
        }
        //删除
        for (vector<pair<int, int> >::iterator i = mFlag.begin(); i != mFlag.end(); ++i)
        {
            refineMat.at<uchar>(i->first, i->second) = 0;
        }

        //直到没有点满足，算法结束
        if (mFlag.size() == 0) break;
        else mFlag.clear();//将mFlag清空
    }

    cv::threshold(refineMat, refineMat, 0, 255, CV_THRESH_BINARY);//二值化图像
	//}
	m_recover = true;
	if(m_choice == IDM_FACE_CUT)
	{
		m_mat[0] = m_filterMat;
		m_mat[1] = refineMat;
		m_recoverNum = 2;
		ShowImage(refineMat);
	}

	m_filterMat =  refineMat;
	
	//imshow("thin",refineMat);
	//GaussianBlur(refineMat,refineMat,Size(3,3),0,0);
	//imshow("qq",refineMat);
	*/
	
}

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
	int x1,x2,t1,t2;
	for (int i = 0; i < nRows - 1; i++){
		for (int j = 0; j < nCols - 1; j++){
			//根据公式计算
			int pixl_gray = 0;
			if(m_choice == IDM_PREWITT || m_choice ==IDM_SOBEL || m_choice == IDM_FACE_CUT)//Roberts算子
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
	if(m_choice == IDM_EDGE_LOG)//基于高斯型拉普拉斯算子
	{
		//高斯模糊，去掉噪点
		cv::GaussianBlur(gray_img,srcMat,Size(theApp.m_modelMatrix,theApp.m_modelMatrix),0,0);
	}
	
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
	//查找最大值
    double maxVal = 0;
	cv::minMaxLoc(dstMat, NULL, &maxVal);
	if(m_choice == IDM_EDGE_LOG)//基于高斯型拉普拉斯算子
	{
		for (int i = 0; i < nRows; i++){
			for (int j = 0; j <nCols; j++){
				float pos = 0;
				float pos_top = 0;
				float pos_bott = 0;
				float pos_left = 0;
				float pos_right = 0;
				float pos_lt = 0;
				float pos_lb = 0;
				float pos_rt = 0;
				float pos_rb = 0;
				if((i ==0&&j==0)|| (i == 0 && j == nCols-1) || (i == nRows-1 && j == 0 )|| 
					(i == nRows-1 &&j == nCols-1))//四个顶点不进行计算
				{
					continue;
				}

				else if(i-1<0 || i+1>=dstMat.rows)//第一行 //最后一行 只有左右有结果
				{
					pos_left = logArr[i][j-1];
					pos_right = logArr[i][j+1];
				}
				else if(j-1<0 || j+1>=dstMat.cols)//左边一列 //右边一列  只有上下有结果
				{
					pos_top = logArr[i-1][j];
					pos_bott = logArr[i+1][j];
				}
				else//其他所有的
				{
					pos = dstMat.at<uchar>(i, j);
					pos_top = logArr[i-1][j];
					pos_bott = logArr[i+1][j];
					pos_left = logArr[i][j-1];
					pos_right = logArr[i][j+1];
					pos_lt = logArr[i-1][j-1];
					pos_lb = logArr[i+1][j-1];
					pos_rt = logArr[i-1][j+1];
					pos_rb = logArr[i+1][j+1];
				}

				if(pos_top*pos_bott<0&& abs(pos_top-pos_bott)>(maxVal*0.14)) //上下
				{
					dstMat.at<uchar>(i, j) = 255;
					continue;
				}
				if(pos_left*pos_right<0 && abs(pos_left-pos_right)>(maxVal*0.14)) //左右
				{
					dstMat.at<uchar>(i, j) = 255;
					continue;
				}
				if(pos_lt*pos_rb<0 && abs(pos_lt-pos_lb)>(maxVal*0.14)) //左上 右下 对角
				{
					dstMat.at<uchar>(i, j) = 255;
					continue;
				}
				if(pos_rt*pos_lb<0 && abs(pos_rt-pos_rb)>(maxVal*0.14)) //右上 左下 对角
				{
					dstMat.at<uchar>(i, j) = 255;
					continue;
				}
				dstMat.at<uchar>(i, j) = 0;
			}
		}
	}
	//GaussianBlur(dstMat,dstMat,Size(3,3),0,0);
	ShowImage(dstMat);
	m_filterMat = dstMat;//保存高通滤波后的图，用于人脸分割
	//m_last_filter =  m_choice;
	//onFaceCutShow(dstMat);//进行人脸分割

	/*
	//灰度化
	Mat houghMat;
	Mat midMat = dstMat.clone();
    cvtColor(midMat, houghMat, CV_GRAY2BGR);
	vector<Vec4i> lines;
    //与HoughLines不同的是，HoughLinesP得到lines的是含有直线上点的坐标的，所以下面进行划线时就不再需要自己求出两个点来确定唯一的直线了
    HoughLinesP(midMat, lines, 1, CV_PI / 180, 30, 50, 10);//注意第五个参数，为阈值

    //依次画出每条线段
    for (size_t i = 0; i < lines.size(); i++)
    {
        Vec4i l = lines[i];

        line(houghMat, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255)); //Scalar函数用于调节线段颜色
	}
	imshow("",houghMat);

	*/
	//释放二维数组（反过来） 
    for(int i=0;i<nRows;i++)
        delete[] logArr[i]; 
    delete[] logArr;
	/*  //用OpenCV调用方法 实现拉普拉斯算子
	//高斯模糊，去掉噪点
	//GaussianBlur(imat,blur_dst,Size(3,3),0,0);
	if(chanels == 1)
	{
		Laplacian(imat,dstMat,CV_8UC1);
	}
	else
	{
		//转为灰度图
		cvtColor(imat,gray_img,CV_BGR2GRAY);
		//拉普拉斯
		Laplacian(gray_img,dstMat,CV_16S);
	}
	//用于实现对整个图像数组中的每一个元素 标定
	//convertScaleAbs(dstMat,dstMat);
	//用来进行对图像（二维数组）的二值化阈值处理
	//threshold(dstMat,dstMat,2,255,THRESH_OTSU|THRESH_BINARY);
	*/
	
	/*
	//用于实现对整个图像数组中的每一个元素 标定
	convertScaleAbs(dstMat,dstMat);
	//用来进行对图像（二维数组）的二值化阈值处理
	threshold(dstMat,dstMat,2,255,THRESH_OTSU|THRESH_BINARY);

	blur_dst = dstMat + gray_img;
	imshow("blur_dst",blur_dst);
	
	ShowImage(dstMat);*/
	
}

void CPImageApp::OnMaxFilterShow()//空域最大值滤波 最大值滤波的输出值是邻域内像素的最亮点，因此，最大值滤波能够有效地滤除椒噪声
								//最小值滤波输出是邻域内像素的最暗点，因此，最小值滤波能够有效地滤除盐噪声
{
	m_recover = true;
	Mat imat = ReadImage();
	// 输入图像判断
    if (imat.empty())
        return;

	saltAndPeper(imat,256);
	//cv::imshow("加入椒盐噪声后的图片",imat);

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
	if(m_choice == IDM_MAX_FILTER || m_choice == IDM_MIN)//最大值滤波  //最小值滤波
	{
		m_mat[0] = imat;
		m_mat[1] = dst;
		m_recoverNum = 2;
		ShowImage(dst);
	}
}

void CPImageApp::OnMedianFilterShow()//空域中值滤波
{
	m_recover = true;
	Mat imat = ReadImage();
	// 输入图像判断
    if (imat.empty())
        return;
	saltAndPeper(imat,256);
	//salt(imat,3000);//加入盐噪声255
	//pepper(imat,3000);//加入椒噪声0
	//cv::imshow("加入椒盐噪声后的图片",imat);
	
	Mat gray_img,dstMat;
	int chanels = imat.channels();
	RGBtoGRAY(imat,gray_img);//RGB转换GRAY
	int nRows = gray_img.rows;
	int nCols = gray_img.cols;
	Mat dst = Mat::zeros(nRows,nCols, CV_8U);

	int max_min; //
	//动态数组
	int *logArr=new int[theApp.m_modelMatrix * theApp.m_modelMatrix];//用于标记像素有没有被处理过
	for (int i = 0; i < theApp.m_modelMatrix * theApp.m_modelMatrix; i++)
	{
		logArr[i]= 0;//为每行分配空间（每行中有col个元素）
		
	}
	//中值滤波
	for (int i = 0; i < nRows - 1; i++)
	{
		for (int j = 0; j <nCols - 1; j++)
		{
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
						int w = theApp.m_text[countModelMatrix-1];
						int p_gray = gray_img.at<uchar>(p, q);
						logArr[countModelMatrix-1] =  w * p_gray;//计算权重与像素灰度之和
						
					}
				}
			}
			sort(logArr,&logArr[countModelMatrix-1]);
			//int qaa = logArr[(countModelMatrix-1)/2];
			dst.at<uchar>(i, j) = logArr[(countModelMatrix-1)/2];
		}
	}

	m_mat[0] = imat;
	m_mat[1] = dst;
	m_recoverNum = 2;
	ShowImage(dst);
	/*
	Mat resutl;
	int ksize = theApp.m_modelMatrix;
	medianBlur(imat,resutl,ksize);
	ShowImage(resutl);
	*/
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
	m_recover = true;
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

	m_mat[0] = histImg_src; //原图直方图
	m_mat[1] = histImg_ref ; //目标直方图 
	m_mat[2] = histImg_res;//规定化后直方图 
	m_mat[3] = res_img; //直方图规定化后图像
	m_mat[4] =  ref_img;//目标图
	m_recoverNum = 5;
	ShowImage(ref_img);//原图
	//imshow("原图", gray_img);
   // imshow("原图直方图", histImg_src);
   // imshow("目标图", ref_img);
   // imshow("目标直方图", histImg_ref);
	//ShowImage(res_img);
   // imshow("直方图规定化后图像", res_img);
  //  imshow("规定化后直方图", histImg_res);



}

void CPImageApp::OnHistogramEqualizationShow()//直方图均衡化
{
	
	//imshow("",writeImage);

}

void CPImageApp::OnHistogramGrayShow()//显示直方图 //直方图均衡化
{
	m_recover = true;
	Mat imat = ReadImage();
	// 输入图像判断
    if (imat.empty())
        return;
	
	Mat gray_img;
	RGBtoGRAY(imat,gray_img);//RGB转换GRAY
	Mat writeImage;
	Mat histImg_ref;
	if(m_choice == ID_HISTOGRAM_EQUALIZATION)//如果是直方图均衡化
	{
		vector<Mat>channelImage;
		split(gray_img,channelImage);

		for(int i = 0; i< gray_img.channels(); i++)
		{
			cv::equalizeHist(channelImage[i], channelImage[i]);//直方图均衡化
		}

		merge(channelImage, writeImage);
		//ShowImage(writeImage);
		Histogram1D hist4;
		histImg_ref = hist4.getHistogramImage(writeImage,m_choice);//目标图
		//imshow("均衡化直方图", histImg_ref);
	}
	Histogram1D hist3;
    Mat histImg_src = hist3.getHistogramImage(gray_img,m_choice);//原图
   
   // Histogram1D hist5;
   // Mat histImg_res = hist5.getHistogramImage(res_img);//结果正规化图
	if(m_choice == IDM_HISTOGRAM_GRAY)
	{
		m_mat[0] = histImg_src;
		m_recoverNum = 1;
		ShowImage(histImg_src);
	}

	if(m_choice == IDM_HISTOGRAM_EQUALIZATION)
	{
		m_mat[0] = histImg_src;
		m_mat[1] = histImg_ref;
		m_mat[2] = writeImage;
		m_recoverNum = 3;
		ShowImage(writeImage);
	}
	
	//imshow("原图直方图", histImg_src);
   // imshow("目标图", ref_img);
   // imshow("目标直方图", histImg_ref);
	//
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
	/*
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
	*/
	int c = theApp.m_text[0];
	Mat resultImage = Mat::zeros(imat.size(), imat.type());
	double gray = 0;
	for (int i = 0; i < imat.rows; i++)
	{
		for (int j = 0; j < imat.cols; j++)
		{
			gray = (double)imat.at<uchar>(i, j);
			gray = c*log((double)(1 + gray));
			resultImage.at<uchar>(i, j) = saturate_cast<uchar>(gray);
		}
	}
	//归一化处理
	normalize(resultImage, resultImage, 0, 255, NORM_MINMAX);
	convertScaleAbs(resultImage, resultImage);

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
	//if(m_choice == IDM_DSCRETCH || m_choice == IDM_LAYER)
//	{
		 //获取图片的一些属性  
		int RowsNum = imat.rows;
		int ColsNum = imat.cols;
		float k, b;//斜率
		//查找最大值
		double max = 0;
		double min = 0;

		cv::minMaxLoc(gray_img, &min, &max);
		
		//Mat dstImg(gray_img.size(), CV_32FC1);
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
		
		int start = 0;
		int end = 0;
		if(m_choice == IDM_LAYER)
		{
			start = theApp.m_text[0];//A
			end = theApp.m_text[1];//B
			//int a = theApp.m_text[0], b = theApp.m_text[1];
			if(start>end)
			{
				int value = start;
				start = end;
				end = value;
			}
			if(start<min)//如果比最小灰度值小
			{
				start = min;		
			}
			if(end>max)//如果比最大灰度值大
			{
				end = max;
			}
		}

		float  strdata = 0;
		for (int i = 0; i < RowsNum; i++)
		{
			//uchar *srcData = gray_img.ptr<uchar>(i);
			for (int j = 0; j < ColsNum; j++)
			{
				strdata = gray_img.at<uchar>(i,j);
				if(m_choice == IDM_DSCRETCH) //对比度拉伸
				{
					if(theApp.m_default == false)
					{
						
						if(strdata>=0 && strdata<x1)
						{
							dstImg.at<uchar>(i, j) = strdata * k1 + b1;
						}
						else if(strdata>=x1 && strdata<x2 )
						{
							dstImg.at<uchar>(i, j) = strdata* k2 + b2;
						}
						else if(strdata>=x2 && strdata<255)
						{
							dstImg.at<uchar>(i, j) = strdata * k3 + b3;
						}
					}
					else
					{
						dstImg.at<uchar>(i, j) = strdata* k + b;
					}
					
				}
				else if(m_choice == IDM_LAYER) //灰度级分层
				{
					
					if(strdata>= start && strdata<= end)
					{
						dstImg.at<uchar>(i, j) = 255;
					}
					else
					{
						dstImg.at<uchar>(i, j) = 10;

					}
				
				}
			}
		}
		//Mat dstmat(dstImg.size(), CV_8UC1);
		ShowImage(dstImg);
	

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


void CPImageApp::OnWhite()
{
	m_choice = IDM_WHITE;
	OnMenu();
}


void CPImageApp::OnScreshot()//截取区域
{
	m_choice = IDM_SCRESHOT;
	OnMenu();

}


void CPImageApp::OnFrestore()//区域复原
{
	m_choice = IDM_FRESTORE;
	OnMenu();

}


void CPImageApp::OnRestorefuc()//退化函数
{
	m_choice = IDM_RESTOREFUC;
	OnMenu();

}


void CPImageApp::OnReverfilter()//逆滤波复原
{
	m_choice = IDM_REVERFILTER;
	OnMenu();

}


void CPImageApp::OnThreshold()
{
	m_choice = IDM_THRESHOLD;
	//CLogDlg dlg;
	//dlg.setDlgTitle("基本全局阈值",IDM_THRESHOLD);
	//dlg.DoModal();
	OnMenu();
}


void CPImageApp::OnGlobalThreshold()
{
	m_choice = IDM_GLOBAL_THRESHOLD;
	
	OnMenu();
}


void CPImageApp::OnOtsuThreshold()
{
	m_choice = IDM_OTSU_THRESHOLD;
	
	OnMenu();
}


void CPImageApp::OnEdgeDetect()
{
	m_choice = IDM_EDGE_DETECT;
	
	OnMenu();
}


void CPImageApp::OnEdgeSobel()
{
	m_choice = IDM_SOBEL;
	CSharpenDlg dlg;
	dlg.setDlgTitle("Sobel 算子",IDM_SOBEL);
	dlg.DoModal();
	OnMenu();
}


void CPImageApp::OnEdgeLapla()
{
	m_choice = IDM_LA_FILTER;
	CSmoothDlg dlg;
	dlg.setDlgTitle("拉普拉斯算子",IDM_LA_FILTER);
	dlg.DoModal();
	OnMenu();
}


void CPImageApp::OnEdgeLog()
{
	m_choice = IDM_EDGE_LOG;
	CSmoothDlg dlg;
	dlg.setDlgTitle("高斯型拉普拉斯算子",IDM_EDGE_LOG);
	dlg.DoModal();
	OnMenu();
}

void CPImageApp::OnEdgeCanny()
{
	m_choice = IDM_EDGE_CANNY;
	
	OnMenu();
}

void CPImageApp::OnEdgeHough()
{
	m_choice = IDM_EDGE_HOUGH;
	
	OnMenu();
}

void CPImageApp::OnFieldGrow()//区域生长
{
	m_choice = IDM_FIELD_GROW;
	CLogDlg dlg;
	dlg.setDlgTitle("区域生长",IDM_FIELD_GROW);
	dlg.DoModal();
	OnMenu();
}


void CPImageApp::OnFieldSpo()//区域分裂与聚合
{
	m_choice = IDM_FIELD_SPO;
	
	OnMenu();
}


void CPImageApp::OnFaceCut()
{
	m_choice = IDM_FACE_CUT;
	
	OnMenu();
}

void CPImageApp::OnFaceThre()//人脸分割--阈值处理
{
	m_choice = IDM_FACE_THRE;

	OnMenu();
}

void CPImageApp::OnFaceEdge()//人脸分割--边缘检测
{
	m_choice = IDM_FACE_EDGE;
	
	OnMenu();
}


void CPImageApp::OnFaceFcut()//人脸分割--图片分割
{
	m_choice = IDM_FACE_FCUT;
	
	OnMenu();
}
void CPImageApp::OnFaceTag()
{
	m_choice = IDM_FACE_TAG;
	
	OnMenu();
}

void CPImageApp::OnCutTag()
{
	m_choice = IDM_CUT_TAG;
	
	OnMenu();
}


		
		
		
		
void CPImageApp::OnFaceTop()
{
	m_choice = IDM_FACE_TOP;//提取额头;
	
	OnMenu();
}


void CPImageApp::OnFaceLeft()
{
	m_choice = IDM_FACE_LEFT;//提取左脸颊
	
	OnMenu();

}


void CPImageApp::OnFaceRight()
{
	m_choice = IDM_FACE_RIGHTC ;//提取右脸颊;
	
	OnMenu();

}


void CPImageApp::OnFaceNose()
{
	m_choice = IDM_FACE_NOSE ;//提取鼻子
	
	OnMenu();
}


void CPImageApp::OnFaceBottom()
{
	m_choice = IDM_FACE_BOTTOM;//提取下巴
	
	OnMenu();
	
}

