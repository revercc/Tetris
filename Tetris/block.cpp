#include <Windows.h>
#include "resource.h"
#include <time.h>
HWND		hDlgModeless ;
BOOL CALLBACK ShowWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) ;
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
BOOL CALLBACK AboutWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) ;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	MSG			msg ;
	HWND		hwnd ;
	WNDCLASS	wndclass ;
	HACCEL		hAccel ;
	TCHAR		szAppName[] = TEXT("MyClass") ;
	int				iTitle, iMenu ;					//�������Ͳ˵����ĸ߶�
	
	wndclass.cbClsExtra			= 0 ;				//Ԥ���ռ�������Ƿ�ʼ��Ϸ
	wndclass.cbWndExtra			= sizeof(LONG) ;	
	wndclass.hbrBackground		= (HBRUSH)GetStockObject (WHITE_BRUSH) ;
	wndclass.hCursor			= LoadCursor(NULL, IDC_ARROW) ;
	wndclass.hIcon				= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wndclass.hInstance			= hInstance ;
	wndclass.lpfnWndProc		= WndProc ;
	wndclass.lpszClassName		= szAppName ;
	wndclass.lpszMenuName		= MAKEINTRESOURCE(IDR_MENU1) ;
	wndclass.style				= NULL ;
	
	if(!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("�˳���ֻ����windowNT������!"), szAppName, MB_OK) ;
		return 0 ;
	}

	iTitle	= GetSystemMetrics(SM_CYCAPTION) ;
	iMenu	= GetSystemMetrics(SM_CYMENU) ;
	
	hwnd = CreateWindow(szAppName, TEXT("����˹����"), WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
						100, 20, 600, 800 + iTitle + iMenu, NULL, NULL, hInstance, NULL) ;
	ShowWindow(hwnd, iCmdShow) ;
	//UpdateWindow(hwnd) ;

	hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1)) ;		//������������ڴ�
	while(GetMessage(&msg,NULL, 0, NULL))
	{
		if(hDlgModeless == 0 ||  !IsDialogMessage(hDlgModeless, &msg))
			if(!TranslateAccelerator(hwnd, hAccel, &msg))
			{
				TranslateMessage(&msg) ;
				DispatchMessage(&msg) ;
			}
	}
	return msg.wParam ;
}






int RandRect(int (**a)[4], int (*b)[4], int (*c)[4], int (*d)[4], int (*e)[4], int (*f)[4], int (*g)[4], int (*h)[4], int (*i)[4], int (*j)[4], int (*k)[4], int (*l)[4])

{
	srand((int)time(0));
	int n = (rand() + 1) % 11 + 1;
	switch(n)
	{
	case 1:
		*a = b ;
		break ;
	case 2:
		*a = c ;
		break ;
	case 3:
		*a = d ;
		break ;
	case 4:
		*a = e ;
		break ;
	case 5:
		*a = f ;
		break ;
	case 6:
		*a = g ;
		break ;
	case 7:
		*a = h ;
		break ;
	case 8:
		*a = i ;
		break ;
	case 9:
		*a = j ;
		break ;
	case 10:
		*a = k ;
		break ;
	case 11:
		*a = l;
		break ;
	}
	return n ;
}








LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int		cxClient,cyClient ;
	static int		iX = 120, iY = -160 ;					//���������������Ͻǵ�x��y������
	static int		iSpeed	 = 1 ;				//����������ٶȵȼ����Ѷȵȼ���
	
	static int		iFen = 0 ;					//�÷�
	static int		iTime ;						//ʱ��
	int				iBiaoJi2 = 0;				//������������ש��

	static int      iBiaoJi3 = 0 ;				//���������ж�����Ļ����Ƿ��Ѿ�����ײ�
	static int		iBiaoJi4 = 0 ;				//���������ж��Ƿ��Ѿ���ʼ��Ϸ��
	static int		iBiaoJi5 = 0 ;				//���������ж�ʲôʱ��Ӧ����ʾʱ�䣬


	TCHAR			szBuffer[10] ;
	HDC				hdc ;
	RECT			rect ;
	PAINTSTRUCT		ps ;
	HWND			hStaticRect ;				//��̬�����Ӵ��ڿؼ��ľ��
	static			HMENU		hMenu ;
	static	HWND	hStaticTextFen, hStaticTextOldfen, hStaticTextV, hStaticTextHang, hStaticTextTime ;							//��̬�ı��Ӵ��ڿؼ��ľ��
	static	HWND	hStaticTextFen_num, hStaticTextOldfen_num, hStaticTextV_num, hStaticTextHang_num, hStaticTextTime_num ;		//��̬�ı��Ӵ��ڿؼ��ľ��
	HINSTANCE		hInstance = NULL;
	static	HPEN	hPen1, hPen2, hPen3;
	
	
	static	int		iLeiXing; 
	static	int		iBlock_1[4][4] = { 0, 0, 0, 0,
									   0, 0, 0, 0,
									   0, 0, 1, 1,
									   0, 1, 1, 0 },

					iBlock_2[4][4] = { 0, 0, 0, 0,
									   0, 1, 0, 0,
									   0, 1, 1, 0,
									   0, 0, 1, 0 } ,

					iBlock_3[4][4] = { 0, 0, 0, 0,
									   0, 0, 1, 0,
									   0, 1, 1, 0,
									   0, 1, 0, 0 } ,

					iBlock_4[4][4] = { 0, 0, 0, 0,
									   0, 0, 0, 0,
									   0, 1, 1, 0,
									   0, 0, 1, 1 } ,
					
					
					iBlock_5[4][4] = { 0, 0, 0, 1,
									   0, 0, 0, 1,
									   0, 0, 0, 1,
									   0, 0, 0, 1 },

					iBlock_6[4][4] = { 0, 0, 0, 0,
									   0, 0, 0, 0,
									   0, 0, 0, 0,
									   1, 1, 1, 1 },

					iBlock_7[4][4] = { 0, 0, 0, 0,
									   0, 1, 0, 0,
									   1, 1, 1, 0,
									   0, 0, 0, 0 },

					iBlock_8[4][4] = { 0, 0, 0, 0,
									   0, 1, 0, 0,
									   0, 1, 1, 0,
									   0, 1, 0, 0 },

					iBlock_9[4][4] = { 0, 0, 0, 0,
									   0, 0, 0, 0,
									   1, 1, 1, 0,
									   0, 1, 0, 0 },

					iBlock_10[4][4] = { 0, 0, 0, 0,
										0, 1, 0, 0,
										1, 1, 0, 0,
										0, 1, 0, 0 },

					iBlock_11[4][4] = { 0, 0, 0, 0,
									    0, 0, 0, 0,
									    0, 1, 1, 0,
									    0, 1, 1, 0 } ;
				 
	static	int  	( *iBlock) [4] = NULL;	

	static	int		iBlockZong[21][11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
											1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } ;
switch(message)							
	{
	case WM_CREATE:
		GetClientRect(hwnd, &rect) ;									//��ÿͻ����Ĵ�С
		cxClient = rect.right ;
		cyClient = rect.bottom ;
		hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE) ;		//��ó��򸸴��ڵ�ʵ�����
		


		hStaticRect				= CreateWindow(TEXT("static"), NULL, WS_CHILD | WS_VISIBLE | SS_WHITERECT | WS_BORDER,			//��������ʽ��̬�Ӵ��ڿؼ�����ʾ
												400, 0, 200, 800, hwnd, (HMENU) 1, hInstance, NULL) ; 
		hStaticTextFen			= CreateWindow(TEXT("static"), TEXT("��ǰ����"), WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER, //�����ı�ʽ��̬�Ӵ��ڿؼ�����ʾ
												400, 0, 200, 80, hwnd, (HMENU) 2, hInstance, NULL) ;
		hStaticTextFen_num		= CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
												400, 80, 200, 80, hwnd, (HMENU) 3, hInstance, NULL) ;
		hStaticTextOldfen		= CreateWindow(TEXT("static"), TEXT("��ʷ�߷�"), WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
												400, 160, 200, 80, hwnd, (HMENU) 4, hInstance, NULL) ;
		hStaticTextOldfen_num	= CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
												400, 240, 200, 80, hwnd, (HMENU) 5, hInstance, NULL) ;
		hStaticTextV			= CreateWindow(TEXT("static"), TEXT("�ٶ�"), WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
												400, 320, 200, 80, hwnd, (HMENU) 6, hInstance, NULL) ;
		hStaticTextV_num		= CreateWindow(TEXT("static"), TEXT("1"), WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
												400, 400, 200, 80, hwnd, (HMENU) 7, hInstance, NULL) ;
		hStaticTextHang			= CreateWindow(TEXT("static"), TEXT("��������"), WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
												400, 480, 200, 80, hwnd, (HMENU) 7, hInstance, NULL) ;
		hStaticTextHang_num		= CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
												400, 560, 200, 80, hwnd, (HMENU) 7, hInstance, NULL) ;
		hStaticTextTime			= CreateWindow(TEXT("static"), TEXT("����ʱ��(s)"), WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
												400, 640, 200, 80, hwnd, (HMENU) 7, hInstance, NULL) ;
		hStaticTextTime_num		= CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
												400, 720, 200, 80, hwnd, (HMENU) 7, hInstance, NULL) ;

		
	
		
		iLeiXing = RandRect(&iBlock, iBlock_1, iBlock_2, iBlock_3, iBlock_4, iBlock_5, iBlock_6, iBlock_7, iBlock_8, iBlock_9,iBlock_10, iBlock_11) ;
	
		hPen1 = CreatePen(PS_SOLID, 1, RGB(0,0,0)) ;			//��
		hPen2 = CreatePen(PS_SOLID, 1, RGB(255,255,255)) ;		//��
		hPen3 = CreatePen(PS_SOLID, 1, RGB(255,0,0)) ;			//��


		hMenu = GetMenu(hwnd) ;									//��Ĳ˵����
		

		return 0 ;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps) ;
		
																//��������
	
			for(int i = 1; i <= 20; i++)
			{
				MoveToEx(hdc, 0, i * 40, NULL) ;
				LineTo(hdc, 400, i * 40);
			}
			for(int i = 1; i <= 10; i++)
			{
				MoveToEx(hdc, i * 40, 0, NULL) ;
				LineTo(hdc, i * 40, 800) ;
			}
			

		
		
		for(int x = 0; x < 20; x++)										//�����Ѿ����ڵķ���
			for(int y = 0; y < 10; y++)
			{
				if(iBlockZong[x][y] == 1)
					SelectObject(hdc,hPen3) ;
				else if(iBlockZong[x][y] == 0)
					SelectObject(hdc,hPen2) ;
				for(int i = 1; i <= 38; i++)
				{
					MoveToEx(hdc, y*40+1, x*40 + i, NULL) ;
					LineTo(hdc, y*40 + 39, x*40 + i) ;
				}
			}
				
		for(int x = 0; x < 20; x++)
		{
			for(int y = 0; y < 10; y++)								//��������
				if(iBlockZong[x][y] == 1)
					iBiaoJi2++ ;
			if(iBiaoJi2 == 10 && iBiaoJi3== 1)
			{	
				for(int i = x-1; i >=  0; i--)
					for(int ii = 0; ii < 10; ii++)
						iBlockZong[i+ 1][ii] = iBlockZong[i][ii] ;
				iFen ++;
				
			}

			iBiaoJi2 = 0 ;
		}

		for(int i = 0; i < 10; i++)									//�ж���Ϸ�Ƿ����
			if(iBlockZong[0][i] == 1 && iBiaoJi3 == 1)
			{
				SendMessage(hwnd, WM_COMMAND, ID_40019, 0);			//����ͣ��Ϸ��ʹʱ�Ӳ��ڷ���WM_TIMER
				if( IDOK == MessageBox(NULL, TEXT("��Ϸ���� ,�Ƿ����¿�ʼ��"), TEXT("����˹����"), MB_OKCANCEL | MB_ICONEXCLAMATION | MB_DEFBUTTON1))
					SendMessage(hwnd, WM_COMMAND, ID_40001, 0) ;
				else
					SendMessage(hwnd, WM_DESTROY, 0, 0) ;
			}
	
		iBiaoJi3 = 0 ;
		wsprintf(szBuffer,TEXT("%i"),iFen );								//���û�������ʽ������int����ΪTCHAR���ͣ�,���µ÷ֺ�����
		SetWindowText(hStaticTextHang_num, szBuffer);
		SetWindowText(hStaticTextFen_num, szBuffer);
		EndPaint(hwnd, &ps) ;
		return 0 ;
	case WM_COMMAND:
		if(0 == HIWORD(wParam))
		{
			switch(LOWORD(wParam))				//����˵���
			{
			case ID_40001:						//���¿�ʼ
				iBiaoJi4 = 1 ;
				for(int x = 0; x < 20; x++)
					for(int y =0; y < 10; y++)
						iBlockZong[x][y] = 0 ;
				iTime = 0 ;
				iFen = 0 ;
				iX = 120 ;
				iY = -160 ;
				iLeiXing = RandRect(&iBlock, iBlock_1, iBlock_2, iBlock_3, iBlock_4, iBlock_5, iBlock_6, iBlock_7, iBlock_8, iBlock_9,iBlock_10, iBlock_11) ;
				if(iSpeed == 1)
					SetTimer(hwnd, 1, 1000, NULL);
				else if(iSpeed == 2)
					SetTimer(hwnd, 2, 500, NULL) ;
				else if(iSpeed == 3)
					SetTimer(hwnd, 3, 250, NULL) ;
				SetWindowLong(hwnd, 0, 1) ;
				break ;

			case ID_40002:
				
				if(iBiaoJi4 == 1)
				{
					KillTimer(hwnd, iSpeed) ;
					SetTimer(hwnd, 1, 1000, NULL) ;
				}
				CheckMenuItem (hMenu, ID_40003, MF_UNCHECKED) ;				//�ı�˵���ѡ��״̬
				CheckMenuItem (hMenu, ID_40004, MF_UNCHECKED) ;
				CheckMenuItem (hMenu, ID_40002, MF_CHECKED) ;

				iSpeed = 1 ;
				wsprintf(szBuffer,TEXT("%i"),iSpeed );								
				SetWindowText(hStaticTextV_num, szBuffer);	
				break ;
			case ID_40003:
				if(iBiaoJi4 == 1)
				{
					KillTimer(hwnd, iSpeed) ;					//�������ʱ��

					SetTimer(hwnd, 2, 500, NULL) ;				//�ڶ���ʱ�ӣ�ÿ0.5�뷢��һ��WM_TIMER��Ϣ��
				}
				CheckMenuItem (hMenu, ID_40002, MF_UNCHECKED) ;
				CheckMenuItem (hMenu, ID_40004, MF_UNCHECKED) ;
				CheckMenuItem (hMenu, ID_40003, MF_CHECKED) ;
				
				iSpeed = 2 ;
				wsprintf(szBuffer,TEXT("%i"),iSpeed );								
				SetWindowText(hStaticTextV_num, szBuffer);
				break ;
			case ID_40004:
				if(iBiaoJi4 == 1)
				{
					KillTimer(hwnd, iSpeed) ;				
					SetTimer(hwnd, 3, 250, NULL) ;	
				}
				CheckMenuItem (hMenu, ID_40002, MF_UNCHECKED) ;
				CheckMenuItem (hMenu, ID_40003, MF_UNCHECKED) ;
				CheckMenuItem (hMenu, ID_40004, MF_CHECKED) ;
				
				iSpeed = 3 ;
				wsprintf(szBuffer,TEXT("%i"),iSpeed );								
				SetWindowText(hStaticTextV_num, szBuffer);	
				break ;
			case ID_40005:
				break ;

			case ID_40006:
				break ;
			case ID_40007:
				break ;

			case ID_40008:								//�˳���Ϸ
				SendMessage(hwnd, WM_CLOSE, 0, 0) ;
				break ;

			case ID_40009:
				hDlgModeless = CreateDialog( hInstance,MAKEINTRESOURCE(IDD_DIALOG2) ,hwnd, ShowWndProc);	//ע���ģ̬�Ի�����������ʱ����visibleѡ��ҪTRUE�������䲻����ʾ����ҪShowWindow����ʾ��
				MessageBeep(0) ;
				break ;
			case ID_40010:								//�����Ի���
				DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, AboutWndProc) ;
				break ;
			case ID_40018:								//��ʼ��Ϸ
				iBiaoJi4 = 1 ;
				if(iSpeed == 1)
					SetTimer(hwnd,iSpeed , 1000, NULL) ;
				else if(iSpeed == 2)
					SetTimer(hwnd,iSpeed , 500, NULL) ;
				else if(iSpeed == 3)
					SetTimer(hwnd,iSpeed , 250, NULL) ;
				SetWindowLong(hwnd, 0, 1) ;				//����Ԥ���ռ��ֵ
				break;
			case ID_40019:								//��ͣ��Ϸ
				if(1 == GetWindowLong(hwnd, 0))
				{
					MessageBeep(0) ;
					SetWindowLong(hwnd, 0, 0) ;
					KillTimer(hwnd,iSpeed) ;
					iBiaoJi4 = 0 ;
				}
				break ;
			}
		}
		else if(1 == HIWORD(wParam))			//����˵����ټ�
		{
			switch(LOWORD(wParam))
			{
			case ID_ACCELERATOR40011:
				SendMessage(hwnd, WM_COMMAND, ID_40001, 0) ;
				break ;
			case ID_ACCELERATOR40012:
				SendMessage(hwnd, WM_COMMAND, ID_40006, 0) ;
				break ;
			case ID_ACCELERATOR40013:
				SendMessage(hwnd, WM_COMMAND, ID_40007, 0) ;
				break ;
			case ID_ACCELERATOR40014:
				SendMessage(hwnd, WM_COMMAND, ID_40009, 0) ;
				break ;
			}
		}
		return 0;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_LEFT:
			{
				if(iBiaoJi4 == 1)
				{
				switch(iLeiXing)
				{
				case 1:
					if(((iX + 40) > 0) && (iBlockZong[(iY / 40) + 2 ][(iX / 40) + 1] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) ] == 0))
					{
						iBlockZong[(iY / 40) + 2][(iX / 40) + 3] = 0 ;
						iBlockZong[(iY / 40) + 3][(iX / 40) + 2] = 0 ;
						iBlockZong[(iY / 40) + 2][(iX / 40) + 1] = 1 ;
						iBlockZong[(iY / 40) + 3][(iX / 40) ] = 1 ;
						iX = iX -40 ;
					}
					break ;
				case 2:
					if(((iX + 40) > 0) && (iBlockZong[(iY / 40) + 1 ][(iX / 40) ] == 0) && (iBlockZong[(iY / 40) + 2 ][(iX / 40) ] == 0) && (iBlockZong[(iY / 40) + 3 ][(iX / 40) + 1] == 0))
					{
						iBlockZong[(iY / 40) + 1 ][(iX / 40) + 1] = 0 ;
						iBlockZong[(iY / 40) + 2 ][(iX / 40) + 2] = 0 ;
						iBlockZong[(iY / 40) + 3 ][(iX / 40) + 2] = 0 ;
						iBlockZong[(iY / 40) + 1 ][(iX / 40) ] = 1 ;
						iBlockZong[(iY / 40) + 2 ][(iX / 40) ] = 1 ;
						iBlockZong[(iY / 40) + 3 ][(iX / 40) + 1] = 1 ;
						iX = iX - 40 ;
					}
					break ;
				case 3:
					if(((iX + 40) > 0) && (iBlockZong[(iY / 40) + 1 ][(iX / 40) + 1] == 0) && (iBlockZong[(iY / 40) + 2 ][(iX / 40) ] == 0) && (iBlockZong[(iY / 40) + 3 ][(iX / 40) ] == 0))
					{
						iBlockZong[(iY / 40) + 1 ][(iX / 40) + 2] = 0 ;
						iBlockZong[(iY / 40) + 2 ][(iX / 40) + 2] = 0 ;
						iBlockZong[(iY / 40) + 3 ][(iX / 40) + 1] = 0 ;
						iBlockZong[(iY / 40) + 1 ][(iX / 40) + 1] = 1 ;
						iBlockZong[(iY / 40) + 2 ][(iX / 40) ] = 1 ;
						iBlockZong[(iY / 40) + 3 ][(iX / 40) ] = 1 ;
						iX = iX - 40 ;
					}
					break ;
				case 4:
					if( ((iX + 40) > 0) && (iBlockZong[(iY / 40) + 2][(iX / 40) ] == 0) && ((iBlockZong[(iY / 40) + 3][(iX / 40) + 1] == 0)))
					{
						iBlockZong[(iY / 40) + 2 ][(iX / 40) + 2] = 0 ;
						iBlockZong[(iY / 40) + 3 ][(iX / 40) + 3] = 0 ;
						iBlockZong[(iY / 40) + 2 ][(iX / 40) ] = 1 ;
						iBlockZong[(iY / 40) + 3 ][(iX / 40) + 1] = 1 ;
						iX = iX - 40 ;
					}

					break ;
				case 5:
					if(((iX + 120)> 0) && (iBlockZong[(iY / 40) ][(iX / 40) + 2] == 0) && (iBlockZong[(iY / 40) + 1][(iX / 40) + 2] == 0) && (iBlockZong[(iY / 40) + 2][(iX / 40) + 2] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 2] == 0))
					{
						iBlockZong[(iY / 40) ][(iX / 40) + 2] = 1 ; 
						iBlockZong[(iY / 40) + 1][(iX / 40) + 2] = 1 ;
						iBlockZong[(iY / 40) + 2][(iX / 40) + 2] = 1 ;
						iBlockZong[(iY / 40) + 3][(iX / 40) + 2] = 1 ;
 						
						iBlockZong[(iY / 40) ][(iX / 40) + 3] = 0 ; 
						iBlockZong[(iY / 40) + 1][(iX / 40) + 3] = 0 ;
						iBlockZong[(iY / 40) + 2][(iX / 40) + 3] = 0 ;
						iBlockZong[(iY / 40) + 3][(iX / 40) + 3] = 0 ;
						iX = iX - 40 ;
					}
					break;
				case 6:
					if((iX > 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) - 1] == 0))
					{
						iBlockZong[(iY / 40) + 3][(iX / 40) - 1] = 1 ;
						iBlockZong[(iY / 40) +3][(iX / 40) + 3] = 0 ;
						iX = iX - 40 ;
					}
					break ;
				case 7:
					if((iX > 0) && (iBlockZong[(iY / 40) + 2][(iX / 40) - 1] == 0) && (iBlockZong[(iY / 40) + 1][(iX / 40) ] == 0 ))
					{
						iBlockZong[(iY / 40) + 1][(iX / 40) + 1] = 0 ;
						iBlockZong[(iY / 40) + 2][(iX / 40) + 2] = 0 ;
						iBlockZong[(iY / 40) + 2][(iX / 40) - 1] = 1 ;
						iBlockZong[(iY / 40) + 1][(iX / 40) ] = 1 ;
						iX = iX -  40 ;
					}
					break ;
				case 8:
					if((iX + 40) > 0 && (iBlockZong[(iY / 40) + 1][(iX / 40) ] == 0)&& (iBlockZong[(iY / 40) + 2][(iX / 40) ] == 0) &&(iBlockZong[(iY / 40) + 3][(iX / 40) ] == 0))
					{
						iBlockZong[(iY / 40) + 1][(iX / 40) + 1] = 0 ;
						iBlockZong[(iY / 40) + 2][(iX / 40) + 2] = 0 ;
						iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 0 ;

						iBlockZong[(iY / 40) + 1][(iX / 40) ] = 1 ;
						iBlockZong[(iY / 40) + 2][(iX / 40) ] = 1 ;
						iBlockZong[(iY / 40) + 3][(iX / 40) ] = 1 ;
						iX = iX - 40 ;
					}
					break ;
				case 9:
					if((iX > 0) &&  (iBlockZong[(iY / 40) + 2][(iX / 40) - 1] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) ] == 0))
					{
						iBlockZong[(iY / 40) + 2][(iX / 40) + 2] = 0 ;
						iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 0 ;
						iBlockZong[(iY / 40) + 2][(iX / 40) - 1] = 1 ;
						iBlockZong[(iY / 40) + 1][(iX / 40) + 1] = 0 ;
						iBlockZong[(iY / 40) + 3][(iX / 40) ] = 1 ;
						iX = iX - 40 ;
					}
					break ;
				case 10:
					if((iX > 0) && (iBlockZong[(iY / 40) + 2][(iX / 40) - 1] == 0) &&  (iBlockZong[(iY / 40) + 3][(iX / 40) ] == 0))
					{
						iBlockZong[(iY / 40) + 1][(iX / 40) + 1] = 0 ;
						iBlockZong[(iY / 40) + 2][(iX / 40) + 1] = 0 ;
						iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 0 ;
						iBlockZong[(iY / 40) + 1][(iX / 40) ] = 1 ;
						iBlockZong[(iY / 40) + 2][(iX / 40) - 1] = 1 ;
						iBlockZong[(iY / 40) + 3][(iX / 40)] = 1 ;
						iX = iX - 40 ;
					}
					break ;
				case 11:
					if((iX + 40)> 0 && (iBlockZong[(iY / 40) + 2][(iX / 40) ] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) ] == 0))
					{
						iBlockZong[(iY / 40) + 2][(iX / 40) ] = 1 ;
						iBlockZong[(iY / 40) + 3][(iX / 40) ] = 1 ;
						iBlockZong[(iY / 40) + 2][(iX / 40) + 2] = 0 ;
						iBlockZong[(iY / 40) + 3][(iX / 40) + 2] = 0 ;
						iX = iX - 40 ;
					}
					break ;
				}
			}
			}
			break ;
		case VK_RIGHT:
			if(iBiaoJi4 == 1)
			{
			switch(iLeiXing)
			{
			case 1:
				if((iBlockZong[(iY / 40) + 2][(iX / 40) + 4] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 3] == 0))
				{
					iBlockZong[(iY / 40) + 2][(iX / 40) + 2] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 4] = 1 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 3] = 1 ;
					iX = iX + 40 ;
				}
				break ;
			case 2:
				if((iBlockZong[(iY / 40) + 1][(iX / 40) + 2] == 0) && (iBlockZong[(iY / 40) + 2][(iX / 40) + 3] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 3] == 0))
				{
					iBlockZong[(iY / 40) + 1][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 1][(iX / 40) + 2] = 1 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 2] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 3] = 1 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 3] = 1 ;
					iX = iX + 40 ;
				}
				break ;
			case 3:
				if((iBlockZong[(iY / 40) + 1][(iX / 40) + 3] == 0) && (iBlockZong[(iY / 40) + 2][(iX / 40) + 3] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 2] == 0))
				{
					iBlockZong[(iY / 40) + 1][(iX / 40) + 2] = 0 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 1][(iX / 40) + 3] = 1 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 3] = 1 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 2] = 1 ;
					iX = iX + 40 ;
				}
				break ;
			case 4:
				if((iBlockZong[(iY / 40) + 2][(iX / 40) + 3] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 4] == 0))
				{
					iBlockZong[(iY / 40) + 2][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 2] = 0 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 3] = 1 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 4] = 1 ;
					iX = iX + 40;
				}
				break ;
			case 5:
				if((iBlockZong[(iY / 40) ][(iX / 40) + 4] == 0) && (iBlockZong[(iY / 40) + 1][(iX / 40) + 4] == 0) && (iBlockZong[(iY / 40) + 2][(iX / 40) + 4] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 4] == 0))
				{
					iBlockZong[(iY / 40) ][(iX / 40) +3] = 0 ;
					iBlockZong[(iY / 40) + 1][(iX / 40) + 3] = 0 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 3] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 3] = 0 ;
					iBlockZong[(iY / 40) ][(iX / 40) +4] = 1 ;
					iBlockZong[(iY / 40) + 1][(iX / 40) + 4] = 1 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 4] = 1 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 4] = 1 ;
					iX = iX + 40 ;
				}
				break ;
			case 6:
				if((iBlockZong[(iY / 40) + 3][(iX / 40) + 4] == 0) )
				{
					iBlockZong[(iY / 40) + 3][(iX / 40) ] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 4] = 1 ;
					iX = iX + 40;
				}
				break ;
			case 7:
				if((iBlockZong[(iY / 40) + 1][(iX / 40) + 2] == 0) && (iBlockZong[(iY / 40) + 2][(iX / 40) + 3] == 0))
				{
					iBlockZong[(iY / 40) + 2][(iX / 40) ] = 0 ;
					iBlockZong[(iY / 40) + 1][(iX / 40) + 1] = 0 ;

					iBlockZong[(iY / 40) + 1][(iX / 40) + 2] = 1 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 3] = 1 ;
					iX = iX + 40 ;
				}
				break ;
			case 8:
				if((iBlockZong[(iY / 40) + 1][(iX / 40) + 2] == 0) &&(iBlockZong[(iY / 40) + 3][(iX / 40) + 2] == 0) && (iBlockZong[(iY / 40) + 2][(iX / 40) + 3] == 0))
				{
					iBlockZong[(iY / 40) + 1][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 1][(iX / 40) + 2] = 1 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 2] = 1 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 3] = 1 ;
					iX = iX + 40 ;
				}
				break ;
			case 9:
				if((iBlockZong[(iY / 40) + 2][(iX / 40) + 3] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 2] == 0))
				{
					iBlockZong[(iY / 40) + 2][(iX / 40) ] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 3] = 1 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 2] = 1 ;
					iX = iX + 40 ;
				}
				break ;
			case 10:
				if((iBlockZong[(iY / 40) + 1][(iX / 40) + 2] == 0) && (iBlockZong[(iY / 40) + 2][(iX / 40) + 2] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 2] == 0 ))	
				{
					iBlockZong[(iY / 40) + 2][(iX / 40) ] = 0 ;
					iBlockZong[(iY / 40) + 1][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 1][(iX / 40) + 2] = 1 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 2] = 1 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 2] = 1 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 0 ;
					iX = iX + 40 ;
				}
				break ;
			case 11:
				if( (iBlockZong[(iY / 40) + 2][(iX / 40) + 3] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 3] == 0))
				{
					iBlockZong[(iY / 40) + 2][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 3] = 1 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 3] = 1 ;
					iX = iX + 40 ;
				}
				break ;
			}
			}
			break ;
		case VK_DOWN:
			if(1 == iBiaoJi4)
			{
			switch(iLeiXing)
			{
			case 1:
				if((iBlockZong[(iY / 40) + 3][(iX / 40) + 3] == 0) && (iBlockZong[(iY / 40) + 4][(iX / 40) + 1] == 0) && (iBlockZong[(iY / 40) + 4][(iX / 40) + 2] == 0))
				{	
					iBlockZong[(iY / 40) + 2][(iX / 40) + 2] = 0 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 3] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 4][(iX / 40) + 1] = 1 ;
					iBlockZong[(iY / 40) + 4][(iX / 40) + 2] = 1 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 3] = 1 ;
					iY = iY + 40 ;
				}
				else
				{
					iX = 120 ;
					iY = - 160 ; 
					iBiaoJi3 = 1 ;
					iLeiXing = RandRect(&iBlock, iBlock_1, iBlock_2, iBlock_3, iBlock_4, iBlock_5, iBlock_6, iBlock_7, iBlock_8, iBlock_9,iBlock_10, iBlock_11) ;
				}
				break ;
			case 2:
				if((iBlockZong[(iY / 40) + 3][(iX / 40) + 1] == 0) && (iBlockZong[(iY / 40) + 4][(iX / 40) + 2] == 0))
				{
					iBlockZong[(iY / 40) + 1][(iX / 40) + 1] = 0;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 2] = 0;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 1;
					iBlockZong[(iY / 40) + 4][(iX / 40) + 2] = 1;
					iY = iY + 40 ;
				}
				else
				{
					iX = 120 ;
					iY = -160 ;
					iBiaoJi3 = 1 ;
					iLeiXing = RandRect(&iBlock, iBlock_1, iBlock_2, iBlock_3, iBlock_4, iBlock_5, iBlock_6, iBlock_7, iBlock_8, iBlock_9,iBlock_10, iBlock_11) ;
				}
				break ;
			case 3:
				if((iBlockZong[(iY / 40) + 3][(iX / 40) + 2] == 0) && (iBlockZong[(iY / 40) + 4][(iX / 40) + 1] == 0))
				{	
					iBlockZong[(iY / 40) + 1][(iX / 40) + 2] = 0 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 4][(iX / 40) + 1] = 1 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 2] = 1 ;
					iY = iY + 40 ;
				}
				else
				{
					iX = 120 ;
					iY = -160 ;
					iBiaoJi3 = 1 ;
					iLeiXing = RandRect(&iBlock, iBlock_1, iBlock_2, iBlock_3, iBlock_4, iBlock_5, iBlock_6, iBlock_7, iBlock_8, iBlock_9,iBlock_10, iBlock_11) ;
				}
				break ;
			case 4:
				if((iBlockZong[(iY / 40) + 3][(iX / 40) + 1] == 0) && (iBlockZong[(iY / 40) + 4][(iX / 40) + 2] == 0) && (iBlockZong[(iY / 40) + 4][(iX / 40) + 3] == 0))
				{
					iBlockZong[(iY / 40) + 2][(iX / 40) + 2] = 0 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 3] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 1 ;
					iBlockZong[(iY / 40) + 4][(iX / 40) + 2] = 1 ;
					iBlockZong[(iY / 40) + 4][(iX / 40) + 3] = 1 ;
					iY = iY + 40 ;
				}
				else
				{
					iX = 120 ;
					iY = -160 ;
					iBiaoJi3 = 1 ;
					iLeiXing = RandRect(&iBlock, iBlock_1, iBlock_2, iBlock_3, iBlock_4, iBlock_5, iBlock_6, iBlock_7, iBlock_8, iBlock_9,iBlock_10, iBlock_11) ;
				}
				break ;
			case 5:
				if(iBlockZong[(iY / 40) + 4][(iX / 40) + 3] == 0)
				{
					iBlockZong[(iY / 40) ][(iX / 40) + 3] = 0 ;
					iBlockZong[(iY / 40) + 4][(iX / 40) + 3] = 1 ;
					iY = iY + 40 ;
				}
				else
				{
					iX = 120 ;
					iY = -160 ;
					iBiaoJi3 = 1 ;
					iLeiXing = RandRect(&iBlock, iBlock_1, iBlock_2, iBlock_3, iBlock_4, iBlock_5, iBlock_6, iBlock_7, iBlock_8, iBlock_9,iBlock_10, iBlock_11) ;
				}
				break ;
			case 6:
				if((iBlockZong[(iY / 40) + 4][(iX / 40) ] == 0) && (iBlockZong[(iY / 40) + 4][(iX / 40) + 1] == 0)&& (iBlockZong[(iY / 40) + 4][(iX / 40) + 2] == 0) && (iBlockZong[(iY / 40) + 4][(iX / 40) + 3] == 0))
				{
					iBlockZong[(iY / 40) + 3][(iX / 40) ] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 2] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 3] = 0 ;
					iBlockZong[(iY / 40) + 4][(iX / 40) ] = 1 ;
					iBlockZong[(iY / 40) + 4][(iX / 40) + 1] = 1 ;
					iBlockZong[(iY / 40) + 4][(iX / 40) + 2] = 1 ;
					iBlockZong[(iY / 40) + 4][(iX / 40) + 3] = 1 ;
					iY = iY + 40 ;
				}
				else
				{
					iX = 120 ;
					iY = -160 ;
					iBiaoJi3 = 1 ;
					iLeiXing = RandRect(&iBlock, iBlock_1, iBlock_2, iBlock_3, iBlock_4, iBlock_5, iBlock_6, iBlock_7, iBlock_8, iBlock_9,iBlock_10, iBlock_11) ;
				}
				break ;
			case 7:
				if((iBlockZong[(iY / 40) + 3][(iX / 40) ] == 0) &&(iBlockZong[(iY / 40) + 3][(iX / 40) + 1] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 2] == 0))
				{
					iBlockZong[(iY / 40) + 1][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) ] = 0 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 2] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) ] = 1 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 1 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 2] = 1 ;
					iY = iY + 40 ;
				}
				else
				{
					iX = 120 ;
					iY = -160 ;
					iBiaoJi3 = 1 ;
					iLeiXing = RandRect(&iBlock, iBlock_1, iBlock_2, iBlock_3, iBlock_4, iBlock_5, iBlock_6, iBlock_7, iBlock_8, iBlock_9,iBlock_10, iBlock_11) ;
				}
				break ;
			case 8:
				if((iBlockZong[(iY / 40) + 4][(iX / 40) + 1] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 2] == 0))
				{
					iBlockZong[(iY / 40) + 1][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 4][(iX / 40) + 1] = 1 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 2] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 2] = 1 ;
					iY = iY + 40 ;
				}
				else
				{
					iX = 120 ;
					iY = -160 ;
					iBiaoJi3 = 1 ;
					iLeiXing = RandRect(&iBlock, iBlock_1, iBlock_2, iBlock_3, iBlock_4, iBlock_5, iBlock_6, iBlock_7, iBlock_8, iBlock_9,iBlock_10, iBlock_11) ;
				}
				break ;
			case 9:
				if((iBlockZong[(iY / 40) + 3][(iX / 40) ] == 0) && (iBlockZong[(iY / 40) + 4][(iX / 40) + 1] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 2] == 0))
				{
					iBlockZong[(iY / 40) + 2][(iX / 40)] = 0 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 2] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) ] = 1 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 2] = 1 ;
					iBlockZong[(iY / 40) + 4][(iX / 40) + 1] = 1 ;
					iY = iY + 40 ;
				}
				else
				{
					iX = 120 ;
					iY = -160 ;
					iBiaoJi3 = 1 ;
					iLeiXing = RandRect(&iBlock, iBlock_1, iBlock_2, iBlock_3, iBlock_4, iBlock_5, iBlock_6, iBlock_7, iBlock_8, iBlock_9,iBlock_10, iBlock_11) ;
				}
				break ;
			case 10:
				if((iBlockZong[(iY / 40) + 3][(iX / 40) ] == 0) && (iBlockZong[(iY / 40) + 4][(iX / 40) + 1] == 0))
				{
					iBlockZong[(iY / 40) + 2][(iX / 40) ] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) ] = 1 ;
					iBlockZong[(iY / 40) + 1][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 4][(iX / 40) + 1] = 1 ;
					iY = iY + 40 ;
				}
				else
				{
					iX = 120 ;
					iY = -160 ;
					iBiaoJi3 = 1 ;
					iLeiXing = RandRect(&iBlock, iBlock_1, iBlock_2, iBlock_3, iBlock_4, iBlock_5, iBlock_6, iBlock_7, iBlock_8, iBlock_9,iBlock_10, iBlock_11) ;
				}
				break ;
			case 11:
				if((iBlockZong[(iY / 40) + 4][(iX / 40) + 1] == 0) && (iBlockZong[(iY / 40) + 4][(iX / 40) + 2] == 0) )
				{	
					iBlockZong[(iY / 40) + 2][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 2] = 0 ;
					iBlockZong[(iY / 40) + 4][(iX / 40) + 1] = 1 ;
					iBlockZong[(iY / 40) + 4][(iX / 40) + 2] = 1 ;
					iY = iY + 40 ;
				}	
				else
				{
					iX = 120 ;
					iY = -160 ;
					iBiaoJi3 = 1 ;
					iLeiXing = RandRect(&iBlock, iBlock_1, iBlock_2, iBlock_3, iBlock_4, iBlock_5, iBlock_6, iBlock_7, iBlock_8, iBlock_9,iBlock_10, iBlock_11) ;
				}
				break ;
			}
			}
			break;
			
		case VK_SPACE:
			switch(iLeiXing)
			{
			case 1:
				if( (iBlockZong[(iY / 40) + 1][(iX / 40) + 1] == 0) && (iBlockZong[(iY / 40) + 1][(iX / 40) + 2] == 0) && (iBlockZong[(iY / 40) + 1][(iX / 40) + 3] == 0) && (iBlockZong[(iY / 40) + 2][(iX / 40) + 1] == 0))
				{
					iLeiXing = 2;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 3] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 1][(iX / 40) + 1] = 1 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 1] = 1 ;
				}
				break ;
			case 2:
				if( (iX + 120 != 400) &&(iBlockZong[(iY / 40) + 3][(iX / 40) + 1] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 3] == 0) && (iBlockZong[(iY / 40) + 2][(iX / 40) + 3] == 0))
				{
					iLeiXing = 1;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 3] = 1 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 1 ;
					iBlockZong[(iY / 40) + 1][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 1] = 0 ;
				}
				else if( (iX + 120 == 400) && (iBlockZong[(iY / 40) + 2][(iX / 40) ] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) ] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 1] == 0))
				{
					iLeiXing = 1;
					iX = iX - 40 ;
					iBlockZong[(iY / 40) + 1][(iX / 40) + 2] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 3] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 1 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 2] = 1 ;
				}
				break ;
			
				
			case 3:
				if( (iX + 120 != 400) &&(iBlockZong[(iY / 40) + 1][(iX / 40) + 3] == 0) && (iBlockZong[(iY / 40) + 2][(iX / 40) + 3] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 3] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 2] == 0))
				{
					iLeiXing = 4;
					iBlockZong[(iY / 40) + 1][(iX / 40) + 2] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 2] = 1 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 3] = 1 ;
				}
				else if((iX + 120 == 400) &&(iBlockZong[(iY / 40) + 2][(iX / 40) ] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) ] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 2] == 0))
				{
					iLeiXing = 4;
					iX = iX - 40 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 3] = 0 ;
					iBlockZong[(iY / 40) + 1][(iX / 40) + 3] = 0 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 1] = 1 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 3] = 1 ;
				}
				break ;
			case 4:
				if((iBlockZong[(iY / 40) + 1][(iX / 40) + 1] == 0) && (iBlockZong[(iY / 40) + 1][(iX / 40) + 2] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 1] == 0))
				{
					iLeiXing = 3 ;
					iBlockZong[(iY / 40) + 1][(iX / 40) + 2] = 1 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 1 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 2] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 3] = 0 ;
				}
				break;
				
			case 5:
				if((iX + 160) <= 280 && (iBlockZong[(iY / 40) ][(iX / 40) + 4] == 0) && (iBlockZong[(iY / 40) ][(iX / 40) + 5] == 0) && (iBlockZong[(iY / 40) ][(iX / 40) + 6] == 0) &&
					(iBlockZong[(iY / 40) + 1][(iX / 40) + 4] == 0) && (iBlockZong[(iY / 40) + 1][(iX / 40) + 5] == 0) && (iBlockZong[(iY / 40) + 1][(iX / 40) + 6] == 0)&&
					(iBlockZong[(iY / 40) + 2][(iX / 40) + 4] == 0) && (iBlockZong[(iY / 40) + 2][(iX / 40) + 5] == 0) && (iBlockZong[(iY / 40) + 2][(iX / 40) + 6] == 0)&&
					(iBlockZong[(iY / 40) + 3][(iX / 40) + 4] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 5] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 6] == 0))
				{
					iLeiXing = 6 ;
					iX = iX + 120 ;
					iBlockZong[(iY / 40) ][(iX / 40) ] = 0 ;
					iBlockZong[(iY / 40) +1][(iX / 40) ] = 0 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) ] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 1 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 2] = 1 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 3] = 1 ;
				}
				else if((iX + 160) > 280 && (iBlockZong[(iY / 40) ][(iX / 40) ] == 0) && (iBlockZong[(iY / 40) ][(iX / 40) + 1] == 0) && (iBlockZong[(iY / 40) ][(iX / 40) + 2] == 0) &&
						(iBlockZong[(iY / 40) + 1 ][(iX / 40)] == 0) && (iBlockZong[(iY / 40) + 1][(iX / 40) + 1] == 0) && (iBlockZong[(iY / 40) + 1][(iX / 40) + 2] == 0) &&
						(iBlockZong[(iY / 40) + 2][(iX / 40) ] == 0) && (iBlockZong[(iY / 40) + 2][(iX / 40) + 1] == 0) && (iBlockZong[(iY / 40) + 2][(iX / 40) + 2] == 0) &&
						(iBlockZong[(iY / 40) + 3][(iX / 40) ] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 1] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 2] == 0))
				{
					iLeiXing = 6 ;
					iBlockZong[(iY / 40) ][(iX / 40) + 3] = 0 ;
					iBlockZong[(iY / 40) +1][(iX / 40) + 3] = 0 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 3] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) ] = 1 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 1 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 2] = 1 ;
				}
				break ;

			case 6:
				if( (iBlockZong[(iY / 40) ][(iX / 40) + 3] == 0)   && (iBlockZong[(iY / 40) ][(iX / 40) + 2] == 0)  && (iBlockZong[(iY / 40) ][(iX / 40) + 1] == 0)  && (iBlockZong[(iY / 40) ][(iX / 40) ] == 0) &&
				    (iBlockZong[(iY / 40)+ 1 ][(iX / 40) + 3] == 0)  && (iBlockZong[(iY / 40) + 1][(iX / 40) + 2] == 0)  && (iBlockZong[(iY / 40)+ 1 ][(iX / 40) + 1] == 0)  && (iBlockZong[(iY / 40) + 1][(iX / 40) ] == 0) &&
				    (iBlockZong[(iY / 40)+ 2 ][(iX / 40) + 3] == 0) && (iBlockZong[(iY / 40) + 2][(iX / 40) + 2] == 0)  && (iBlockZong[(iY / 40) + 2][(iX / 40) + 1] == 0) && (iBlockZong[(iY / 40) + 2][(iX / 40) ] == 0))
				{
					iLeiXing  = 5 ;
					iBlockZong[(iY / 40) ][(iX / 40) + 3] = 1 ;
					iBlockZong[(iY / 40) +1][(iX / 40) + 3] = 1 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 3] = 1 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) ] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 2] = 0 ;
				}
				break;
			case 7:
				if( (iBlockZong[(iY / 40) + 1][(iX / 40) ] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 1] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 2] == 0))
				{
					iLeiXing = 8 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) ] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 1 ;
				}
				break ;
			case 8:
				if((iX != 0) &&(iBlockZong[(iY / 40) + 2][(iX / 40) ] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) ] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 2] == 0) && (iBlockZong[(iY / 40) + 1][(iX / 40) + 2] == 0))
				{
					iLeiXing = 9 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) ] = 1 ;
					iBlockZong[(iY / 40) + 1][(iX / 40) + 1] = 0 ;
				}
				else if( iX == 0 && (iBlockZong[(iY / 40) + 1][(iX / 40) +2] == 0) && (iBlockZong[(iY / 40) + 1][(iX / 40) + 3] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 2] == 0))
				{
					iLeiXing = 9;
					iX = iX + 40 ;
					iBlockZong[(iY / 40) + 1][(iX / 40) ] = 0 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 2] = 1 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) ] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 1 ;
				}
				break ;
			case 9:
				if((iX + 80 != 400) && (iBlockZong[(iY / 40) + 1][(iX / 40) ] == 0) && (iBlockZong[(iY / 40) + 1][(iX / 40) + 1] == 0 ) &&(iBlockZong[(iY / 40) + 3][(iX / 40) ] == 0 ) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 2] == 0))
				{
					iLeiXing = 10;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 2] = 0 ;
					iBlockZong[(iY / 40) + 1][(iX / 40) + 1 ] = 1 ;
				}
				else if((iX + 80 == 400) &&(iBlockZong[(iY / 40) + 1][(iX / 40) ] == 0)&& (iBlockZong[(iY / 40) + 2][(iX / 40) - 1] == 0)&& (iBlockZong[(iY / 40) + 3][(iX / 40) ] == 0) )
				{
					iLeiXing = 10;
					iX = iX - 40 ;
					iBlockZong[(iY / 40) + 1][(iX / 40) + 2] = 0 ;
					iBlockZong[(iY / 40) + 3][(iX / 40)+ 2 ] = 0 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) ] = 1 ;
					iBlockZong[(iY / 40) + 1][(iX / 40)+ 1 ] = 1 ;
				}
				break ;
			case 10:
				if((iBlockZong[(iY / 40) + 1][(iX / 40) ] == 0) && (iBlockZong[(iY / 40) + 1][(iX / 40)+ 2 ] == 0) && (iBlockZong[(iY / 40) + 2][(iX / 40) + 2] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) ] == 0))
				{
					iLeiXing = 7;
					iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 0 ;
					iBlockZong[(iY / 40) + 2][(iX / 40) + 2] = 1 ;
				}
				break ;
			case 11:
				break;
			}
			break ;
		}
		InvalidateRect(hwnd, NULL, FALSE);
		UpdateWindow(hwnd) ;
		return 0;
	case WM_TIMER:
		switch(wParam)
		{
		case 1:
			iBiaoJi5 = 4 ;
			break ;
		case 2:
			iBiaoJi5 = iBiaoJi5 + 2 ;
			break ;
		case 3:
			iBiaoJi5++ ;
			break ;
		}
		if(4 == iBiaoJi5 )
		{
			iTime++ ;
			wsprintf(szBuffer,TEXT("%i"),iTime );								//���û�������ʽ������int����ΪTCHAR���ͣ�
			SetWindowText(hStaticTextTime_num, szBuffer);
			iBiaoJi5 = 0 ;
		}
		switch(iLeiXing)
		{
		case 1:
			if((iBlockZong[(iY / 40) + 3][(iX / 40) + 3] == 0) && (iBlockZong[(iY / 40) + 4][(iX / 40) + 1] == 0) && (iBlockZong[(iY / 40) + 4][(iX / 40) + 2] == 0))
			{	
				iBlockZong[(iY / 40) + 2][(iX / 40) + 2] = 0 ;
				iBlockZong[(iY / 40) + 2][(iX / 40) + 3] = 0 ;
				iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 0 ;
				iBlockZong[(iY / 40) + 4][(iX / 40) + 1] = 1 ;
				iBlockZong[(iY / 40) + 4][(iX / 40) + 2] = 1 ;
				iBlockZong[(iY / 40) + 3][(iX / 40) + 3] = 1 ;
				iY = iY + 40 ;
			}
			else
			{
				iX = 120 ;
				iY = - 160 ;
				iBiaoJi3 = 1 ;
				iLeiXing = RandRect(&iBlock, iBlock_1, iBlock_2, iBlock_3, iBlock_4, iBlock_5, iBlock_6, iBlock_7, iBlock_8, iBlock_9,iBlock_10, iBlock_11) ;
			}
			break ;
		case 2:
			if((iBlockZong[(iY / 40) + 3][(iX / 40) + 1] == 0) && (iBlockZong[(iY / 40) + 4][(iX / 40) + 2] == 0))
			{
				iBlockZong[(iY / 40) + 1][(iX / 40) + 1] = 0;
				iBlockZong[(iY / 40) + 2][(iX / 40) + 2] = 0;
				iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 1;
				iBlockZong[(iY / 40) + 4][(iX / 40) + 2] = 1;
				iY = iY + 40 ;
			}
			else
			{
				iX = 120 ;
				iY = -160 ;
				iBiaoJi3 = 1 ;
				iLeiXing = RandRect(&iBlock, iBlock_1, iBlock_2, iBlock_3, iBlock_4, iBlock_5, iBlock_6, iBlock_7, iBlock_8, iBlock_9,iBlock_10, iBlock_11) ;
			}
			break ;
		case 3:
			if((iBlockZong[(iY / 40) + 3][(iX / 40) + 2] == 0) && (iBlockZong[(iY / 40) + 4][(iX / 40) + 1] == 0))
			{	
				iBlockZong[(iY / 40) + 1][(iX / 40) + 2] = 0 ;
				iBlockZong[(iY / 40) + 2][(iX / 40) + 1] = 0 ;
				iBlockZong[(iY / 40) + 4][(iX / 40) + 1] = 1 ;
				iBlockZong[(iY / 40) + 3][(iX / 40) + 2] = 1 ;
				iY = iY + 40 ;
			}
			else
			{
				iX = 120 ;
				iY = -160 ;
				iBiaoJi3 = 1 ;
				iLeiXing = RandRect(&iBlock, iBlock_1, iBlock_2, iBlock_3, iBlock_4, iBlock_5, iBlock_6, iBlock_7, iBlock_8, iBlock_9,iBlock_10, iBlock_11) ;
			}
			break ;
		case 4:
			if((iBlockZong[(iY / 40) + 3][(iX / 40) + 1] == 0) && (iBlockZong[(iY / 40) + 4][(iX / 40) + 2] == 0) && (iBlockZong[(iY / 40) + 4][(iX / 40) + 3] == 0))
			{
				iBlockZong[(iY / 40) + 2][(iX / 40) + 2] = 0 ;
				iBlockZong[(iY / 40) + 2][(iX / 40) + 1] = 0 ;
				iBlockZong[(iY / 40) + 3][(iX / 40) + 3] = 0 ;
				iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 1 ;
				iBlockZong[(iY / 40) + 4][(iX / 40) + 2] = 1 ;
				iBlockZong[(iY / 40) + 4][(iX / 40) + 3] = 1 ;
				iY = iY + 40 ;
			}
			else
			{
				iX = 120 ;
				iY = -160 ;
				iBiaoJi3 = 1 ;
				iLeiXing = RandRect(&iBlock, iBlock_1, iBlock_2, iBlock_3, iBlock_4, iBlock_5, iBlock_6, iBlock_7, iBlock_8, iBlock_9,iBlock_10, iBlock_11) ;
			}
			break ;
		case 5:
			if(iBlockZong[(iY / 40) + 4][(iX / 40) + 3] == 0)
			{
				iBlockZong[(iY / 40) ][(iX / 40) + 3] = 0 ;
				iBlockZong[(iY / 40) + 4][(iX / 40) + 3] = 1 ;
				iY = iY + 40 ;
			}
			else
			{
				iX = 120 ;
				iY = -160 ;
				iBiaoJi3 = 1 ;
				iLeiXing = RandRect(&iBlock, iBlock_1, iBlock_2, iBlock_3, iBlock_4, iBlock_5, iBlock_6, iBlock_7, iBlock_8, iBlock_9,iBlock_10, iBlock_11) ;
			}
			break ;
		case 6:
			if((iBlockZong[(iY / 40) + 4][(iX / 40) ] == 0) && (iBlockZong[(iY / 40) + 4][(iX / 40) + 1] == 0)&& (iBlockZong[(iY / 40) + 4][(iX / 40) + 2] == 0) && (iBlockZong[(iY / 40) + 4][(iX / 40) + 3] == 0))
			{
				iBlockZong[(iY / 40) + 3][(iX / 40) ] = 0 ;
				iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 0 ;
				iBlockZong[(iY / 40) + 3][(iX / 40) + 2] = 0 ;
				iBlockZong[(iY / 40) + 3][(iX / 40) + 3] = 0 ;
				iBlockZong[(iY / 40) + 4][(iX / 40) ] = 1 ;
				iBlockZong[(iY / 40) + 4][(iX / 40) + 1] = 1 ;
				iBlockZong[(iY / 40) + 4][(iX / 40) + 2] = 1 ;
				iBlockZong[(iY / 40) + 4][(iX / 40) + 3] = 1 ;
				iY = iY + 40 ;
			}
			else
			{
				iX = 120 ;
				iY = -160 ;
				iBiaoJi3 = 1 ;
				iLeiXing = RandRect(&iBlock, iBlock_1, iBlock_2, iBlock_3, iBlock_4, iBlock_5, iBlock_6, iBlock_7, iBlock_8, iBlock_9,iBlock_10, iBlock_11) ;
			}
			break ;
		case 7:
			if((iBlockZong[(iY / 40) + 3][(iX / 40) ] == 0) &&(iBlockZong[(iY / 40) + 3][(iX / 40) + 1] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 2] == 0))
			{
				iBlockZong[(iY / 40) + 1][(iX / 40) + 1] = 0 ;
				iBlockZong[(iY / 40) + 2][(iX / 40) ] = 0 ;
				iBlockZong[(iY / 40) + 2][(iX / 40) + 2] = 0 ;
				iBlockZong[(iY / 40) + 3][(iX / 40) ] = 1 ;
				iBlockZong[(iY / 40) + 3][(iX / 40) + 1] = 1 ;
				iBlockZong[(iY / 40) + 3][(iX / 40) + 2] = 1 ;
				iY = iY + 40 ;
			}
			else
			{
				iX = 120 ;
				iY = -160 ;
				iBiaoJi3 = 1 ;
				iLeiXing = RandRect(&iBlock, iBlock_1, iBlock_2, iBlock_3, iBlock_4, iBlock_5, iBlock_6, iBlock_7, iBlock_8, iBlock_9,iBlock_10, iBlock_11) ;
			}
			break ;
		case 8:
			if((iBlockZong[(iY / 40) + 4][(iX / 40) + 1] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 2] == 0))
			{
				iBlockZong[(iY / 40) + 1][(iX / 40) + 1] = 0 ;
				iBlockZong[(iY / 40) + 4][(iX / 40) + 1] = 1 ;
				iBlockZong[(iY / 40) + 2][(iX / 40) + 2] = 0 ;
				iBlockZong[(iY / 40) + 3][(iX / 40) + 2] = 1 ;
				iY = iY + 40 ;
			}
			else
			{
				iX = 120 ;
				iY = -160 ;
				iBiaoJi3 = 1 ;
				iLeiXing = RandRect(&iBlock, iBlock_1, iBlock_2, iBlock_3, iBlock_4, iBlock_5, iBlock_6, iBlock_7, iBlock_8, iBlock_9,iBlock_10, iBlock_11) ;
			}
			break ;
		case 9:
			if((iBlockZong[(iY / 40) + 3][(iX / 40) ] == 0) && (iBlockZong[(iY / 40) + 4][(iX / 40) + 1] == 0) && (iBlockZong[(iY / 40) + 3][(iX / 40) + 2] == 0))
			{
				iBlockZong[(iY / 40) + 2][(iX / 40)] = 0 ;
				iBlockZong[(iY / 40) + 2][(iX / 40) + 1] = 0 ;
				iBlockZong[(iY / 40) + 2][(iX / 40) + 2] = 0 ;
				iBlockZong[(iY / 40) + 3][(iX / 40) ] = 1 ;
				iBlockZong[(iY / 40) + 3][(iX / 40) + 2] = 1 ;
				iBlockZong[(iY / 40) + 4][(iX / 40) + 1] = 1 ;
				iY = iY + 40 ;
			}
			else
			{
				iX = 120 ;
				iY = -160 ;
				iBiaoJi3 = 1 ;
				iLeiXing = RandRect(&iBlock, iBlock_1, iBlock_2, iBlock_3, iBlock_4, iBlock_5, iBlock_6, iBlock_7, iBlock_8, iBlock_9,iBlock_10, iBlock_11) ;
			}
			break ;
		case 10:
			if((iBlockZong[(iY / 40) + 3][(iX / 40) ] == 0) && (iBlockZong[(iY / 40) + 4][(iX / 40) + 1] == 0))
			{
				iBlockZong[(iY / 40) + 2][(iX / 40) ] = 0 ;
				iBlockZong[(iY / 40) + 3][(iX / 40) ] = 1 ;
				iBlockZong[(iY / 40) + 1][(iX / 40) + 1] = 0 ;
				iBlockZong[(iY / 40) + 4][(iX / 40) + 1] = 1 ;
				iY = iY + 40 ;
			}
			else
			{
				iX = 120 ;
				iY = -160 ;
				iBiaoJi3 = 1 ;
				iLeiXing = RandRect(&iBlock, iBlock_1, iBlock_2, iBlock_3, iBlock_4, iBlock_5, iBlock_6, iBlock_7, iBlock_8, iBlock_9,iBlock_10, iBlock_11) ;
			}
			break ;
		case 11:
			if((iBlockZong[(iY / 40) + 4][(iX / 40) + 1] == 0) && (iBlockZong[(iY / 40) + 4][(iX / 40) + 2] == 0) )
			{
				iBlockZong[(iY / 40) + 2][(iX / 40) + 1] = 0 ;
				iBlockZong[(iY / 40) + 2][(iX / 40) + 2] = 0 ;
				iBlockZong[(iY / 40) + 4][(iX / 40) + 1] = 1 ;
				iBlockZong[(iY / 40) + 4][(iX / 40) + 2] = 1 ;
				iY = iY + 40 ;
			}
			else
			{
				iX = 120 ;
				iY = -160 ;
				iBiaoJi3 = 1 ;
				iLeiXing = RandRect(&iBlock, iBlock_1, iBlock_2, iBlock_3, iBlock_4, iBlock_5, iBlock_6, iBlock_7, iBlock_8, iBlock_9,iBlock_10, iBlock_11) ;
			}
			break ;
			}


		InvalidateRect(hwnd, NULL, FALSE);
		UpdateWindow(hwnd) ;
		return 0 ;
	case WM_DESTROY:
			KillTimer(hwnd, iSpeed) ;
			DeleteObject(hPen1) ;
			DeleteObject(hPen2) ;
			DeleteObject(hPen3) ;
		PostQuitMessage(0) ;
		return 0 ;
	case WM_CLOSE:
		if(IDOK == MessageBox(NULL,TEXT("ȷ��Ҫ�رմ��ڲ��˳���Ϸ��"), TEXT("����˹����"), MB_OKCANCEL | MB_ICONEXCLAMATION | MB_DEFBUTTON1))
			DestroyWindow(hwnd) ;
		else
			return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam) ; 
}





BOOL CALLBACK AboutWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)			//ģ̬�Ի����  �Ի������
{
	switch(message)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hwnd, 0) ;
			return TRUE;
		}
		break ;
	}
	return FALSE;
}

BOOL CALLBACK ShowWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDCANCEL:
			hDlgModeless = NULL ;
			DestroyWindow(hwnd) ;
			break ;
		}
		return TRUE;
	}
	return FALSE;
}

