// DllMainFrom.cpp: 实现文件
//

#include "pch.h"
#include "PlantsVsZombies.h"
#include "DllMainFrom.h"
#include "afxdialogex.h"

#include <map>

using namespace std;

map<int, const char*>g_plantNames{
    {0,"豌豆"},
    {1,"向日葵"},
    {2,"樱桃炸弹"},
    {3,"坚果墙"},
    {4,"土豆雷"},
    {5,"寒冰射手"},
    {6,"大嘴花"},
    {7,"双发射手"},
    {8,"小喷菇"},
    {9,"阳光菇"},
    {10,"大喷菇"},
    {11,"墓碑吞噬者"},
    {12,"魅惑菇"},
    {13,"胆小菇"},
    {14,"寒冰菇"},
    {15,"毁灭菇"},
    {16,"睡莲"},
    {17,"窝瓜"},
    {18,"三线射手"},
    {19,"缠绕海草"},
    {20,"火爆辣椒"},
    {21,"地刺"},
    {22,"火炬树桩"},
    {23,"高坚果"},
    {24,"海蘑菇"},
    {25,"路灯花"},
    {26,"仙人掌"},
    {27,"三叶草"},
    {28,"裂荚射手"},
    {29,"杨桃"},
    {30,"南瓜头"},
    {31,"磁力菇"},
    {32,"卷心菜投手"},
    {33,"花盆"},
    {34,"玉米投手"},
    {35,"咖啡豆"},
    {36,"大蒜"},
    {37,"叶子保护伞"},
    {38,"金盏花"},
    {39,"西瓜投手"},
    {40,"机枪射手"},
    {41,"双子向日葵"},
    {42,"忧郁蘑菇"},
    {43,"香蒲"},
    {44,"冰瓜"},
    {45,"吸金磁"},
    {46,"地刺王"},
    {47,"玉米加农炮"},
    {48,"模仿者"},
    {49,"爆炸坚果"},
    {50,"巨大坚果墙"},
    {51,"发芽"},
    {52,"双发射手（往左边）"}
};
// DllMainFrom 对话框

IMPLEMENT_DYNAMIC(DllMainFrom, CDialogEx)

DllMainFrom::DllMainFrom(CWnd* pParent /*=nullptr*/)
    : CDialogEx(DLG_MAINFROM, pParent)
{

}

DllMainFrom::~DllMainFrom()
{
}

void DllMainFrom::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, EDT_PLANT_ID, m_edtPlantID);
    DDX_Control(pDX, EDT_PLANT_X, m_edtPlantX);
    DDX_Control(pDX, EDT_PLANT_Y, m_edtPlantY);
    DDX_Control(pDX, EDT_GET_PLANT_INFO, m_edtPlantInfo);
    DDX_Control(pDX, EDT_GET_CARD_INFO, m_edtCardInfo);
    DDX_Control(pDX, BTN_AUTOBOMB1, m_btnAutoBomb1);
    DDX_Control(pDX, BTN_AUTOBOMB2, m_btnAutoBomb2);
    DDX_Control(pDX, BTN_AUTOCOLLECTSUN, m_btnAutoCollectSun);
}


BEGIN_MESSAGE_MAP(DllMainFrom, CDialogEx)
    ON_BN_CLICKED(BTN_SET_SUNNUM, &DllMainFrom::OnBnClickedSetSunnum)
    ON_BN_CLICKED(BTN_PLANT, &DllMainFrom::OnBnClickedPlant)
    ON_WM_TIMER()
    ON_BN_CLICKED(BTN_SET_CARD_PLANT_CD, &DllMainFrom::OnBnClickedSetCardPlantCd)
    ON_BN_CLICKED(BTN_SET_PLANT_HEALTH, &DllMainFrom::OnBnClickedSetPlantHealth)
    ON_BN_CLICKED(BTN_PLANTDP_1, &DllMainFrom::OnBnClickedPlantdp1)
    ON_BN_CLICKED(BTN_PLANTDP_2, &DllMainFrom::OnBnClickedPlantdp2)
    ON_BN_CLICKED(BTN_AUTOBOMB1, &DllMainFrom::OnBnClickedAutobomb1)
    ON_BN_CLICKED(BTN_AUTOBOMB2, &DllMainFrom::OnBnClickedAutobomb2)
    ON_BN_CLICKED(BTN_AUTOCOLLECTSUN, &DllMainFrom::OnBnClickedAutocollectsun)
END_MESSAGE_MAP()


// DllMainFrom 消息处理程序

BOOL DllMainFrom::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    m_bIsAutoBombMode1 = FALSE;
    m_bIsAutoBombMode2 = FALSE;
    m_bIsAutoCollectSun = FALSE;
    m_hAutoBombThread1 = NULL;
    m_hAutoBombThread2 = NULL;
    m_PlantsVsZombiesBase = (uintptr_t)GetModuleHandle(NULL);
    m_firstOffsetBase = *(uintptr_t*)(m_PlantsVsZombiesBase + 0x2A9EC0);

    // 读取数据间隔
    SetTimer(1, 100, NULL);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // 异常: OCX 属性页应返回 FALSE
}


void DllMainFrom::OnBnClickedSetSunnum()
{
    DWORD dwSecoundOffsetBase = *(DWORD*)(m_firstOffsetBase + 0x768);
    if (dwSecoundOffsetBase == NULL)
    {
        AfxMessageBox("请先进入游戏");
        return;
    }
    DWORD dwSunAddr = dwSecoundOffsetBase + 0x5560;
    *(LPDWORD)dwSunAddr = GetDlgItemInt(EDT_SET_SUNNUMBER);
}


void DllMainFrom::OnBnClickedPlant()
{
    DWORD dwSecoundOffsetBase = *(DWORD*)(m_firstOffsetBase + 0x768);
    if (dwSecoundOffsetBase == NULL)
    {
        AfxMessageBox("请先进入游戏");
        return;
    }
    DWORD dwCallAddr = m_PlantsVsZombiesBase + 0xD120;

    DWORD dwPlantID = GetDlgItemInt(EDT_PLANT_ID);
    DWORD dwPlantX = GetDlgItemInt(EDT_PLANT_X);
    DWORD dwPlantY = GetDlgItemInt(EDT_PLANT_Y);
    __asm {
        pushad
        mov edx, 0xFFFFFFFF
        mov eax, dwPlantID
        push edx
        push eax
        mov eax, dwPlantY
        push dwPlantX
        push dwSecoundOffsetBase
        call dwCallAddr
        popad
    }
}


void DllMainFrom::OnTimer(UINT_PTR nIDEvent)
{
    switch (nIDEvent)
    {
    case 1:
        ShowSunNumber();
        ShowCardInfo();
        // ShowPlantInfo();
        break;
    }
    CDialogEx::OnTimer(nIDEvent);
}

void DllMainFrom::ShowSunNumber()
{
    DWORD dwSecoundOffsetBase = *(DWORD*)(m_firstOffsetBase + 0x768);
    if (dwSecoundOffsetBase == NULL)
    {
        return;
    }
    DWORD dwSunAddr = dwSecoundOffsetBase + 0x5560;
    SetDlgItemInt(EDT_GET_SUNNUMBER, *(LPDWORD)dwSunAddr);
}

void DllMainFrom::ShowCardInfo()
{
    CString fmt;
    DWORD dwSecoundOffsetBase = *(DWORD*)(m_firstOffsetBase + 0x768);
    if (dwSecoundOffsetBase == NULL)
    {
        return;
    }
    DWORD dwThirdOffsetBase = *(DWORD*)(dwSecoundOffsetBase + 0x144);
    // 获取卡片数量
    WORD wCardNumber = *(DWORD*)(dwThirdOffsetBase + 0x24);
    SetDlgItemInt(EDT_GET_CARDNUM, wCardNumber);

    // 获取卡片信息
    m_edtCardInfo.SetWindowText("");
    for (int i = 0; i < wCardNumber; ++i)
    {
        CString strOld;
        // 获取植物ID
        DWORD dwPlantID = *(DWORD*)(dwThirdOffsetBase + i * 0x50 + 0x5c);
        // 获取植物CD
        DWORD dwPlantCD = *(DWORD*)(dwThirdOffsetBase + i * 0x50 + 0x4c);
        fmt.Format("卡槽位置：%d，植物：%s，植物CD：%d\r\n", (i + 1), g_plantNames[dwPlantID], dwPlantCD);
        m_edtCardInfo.GetWindowText(strOld);
        m_edtCardInfo.SetWindowText(strOld + fmt);
    }
}

void DllMainFrom::ShowPlantInfo()
{
    CString fmt;
    DWORD dwSecoundOffsetBase = *(DWORD*)(m_firstOffsetBase + 0x768);
    if (dwSecoundOffsetBase == NULL)
    {
        return;
    }
    // 获取地面种植数量
    DWORD dwPlantNumber = *(DWORD*)(dwSecoundOffsetBase + 0xB0);
    SetDlgItemInt(EDT_GET_PLANTNUM, dwPlantNumber);

    // 获取植物信息
    m_edtPlantInfo.SetWindowText("");
    DWORD dwThirdOffsetBase = *(DWORD*)(dwSecoundOffsetBase + 0xAC);
    for (int i = 0; i < dwPlantNumber; ++i)
    {
        CString strOld;
        auto dwPlantBase = dwThirdOffsetBase + i * 0x14c;
        // 植物种类
        DWORD dwPlantID = *(DWORD*)(dwPlantBase + 0x24);
        // 获取植物X
        DWORD dwPlantX = *(DWORD*)(dwPlantBase + 0x1c);
        // 获取植物Y
        DWORD dwPlantY = *(DWORD*)(dwPlantBase + 0x28);
        // 获取植物血量
        DWORD dwPlantHealth = *(DWORD*)(dwPlantBase + 0x40);
        fmt.Format("植物编号：%d，植物：%s，植物X：%d，植物Y：%d，植物血量：%d\r\n", (i + 1), g_plantNames[dwPlantID], dwPlantX, dwPlantY, dwPlantHealth);
        m_edtPlantInfo.GetWindowText(strOld);
        m_edtPlantInfo.SetWindowText(strOld + fmt);
    }
}


void DllMainFrom::OnBnClickedSetCardPlantCd()
{
    DWORD dwCardNo = GetDlgItemInt(EDT_SET_CARD_ID);
    DWORD dwPlantID = GetDlgItemInt(EDT_SET_CARD_PLANT_ID);
    DWORD dwPlantCD = GetDlgItemInt(EDT_SET_CARD_PLANT_CD);

    if (dwCardNo == 0)
    {
        AfxMessageBox("请输入卡槽编号");
        return;
    }

    DWORD dwSecoundOffsetBase = *(DWORD*)(m_firstOffsetBase + 0x768);
    if (dwSecoundOffsetBase == NULL)
    {
        AfxMessageBox("请先进入游戏");
        return;
    }
    DWORD dwThirdOffsetBase = *(DWORD*)(dwSecoundOffsetBase + 0x144);
    // 设置植物ID
    *(DWORD*)(dwThirdOffsetBase + (dwCardNo - 1) * 0x50 + 0x5c) = dwPlantID;
    // 设置植物CD
    *(DWORD*)(dwThirdOffsetBase + (dwCardNo - 1) * 0x50 + 0x4c) = dwPlantCD;
}


void DllMainFrom::OnBnClickedSetPlantHealth()
{
    DWORD dwPlantMapNo = GetDlgItemInt(EDT_SET_PLANT_ID);
    DWORD dwPlantHealth = GetDlgItemInt(EDT_SET_PLANT_HEALTH);

    if (dwPlantMapNo == 0)
    {
        AfxMessageBox("请输入卡槽编号");
        return;
    }

    // 设置植物血量
    DWORD dwSecoundOffsetBase = *(DWORD*)(m_firstOffsetBase + 0x768);
    if (dwSecoundOffsetBase == NULL)
    {
        AfxMessageBox("请先进入游戏");
        return;
    }
    DWORD dwThirdOffsetBase = *(DWORD*)(dwSecoundOffsetBase + 0xAC);
    *(DWORD*)(dwThirdOffsetBase + (dwPlantMapNo - 1) * 0x14c + 0x40) = dwPlantHealth;

}


void DllMainFrom::OnBnClickedPlantdp1()
{
    DWORD dwSecoundOffsetBase = *(DWORD*)(m_firstOffsetBase + 0x768);
    if (dwSecoundOffsetBase == NULL)
    {
        AfxMessageBox("请先进入游戏");
        return;
    }
    DWORD dwCallAddr = m_PlantsVsZombiesBase + 0xD120;

    for (size_t x = 0; x < 6; x++)
    {
        if (x % 2 != 0)
        {
            continue;
        }
        for (size_t y = 0; y < 5; y++)
        {
            __asm {
                pushad
                mov edx, 0xFFFFFFFF
                mov eax, 47
                push edx
                push eax
                mov eax, y
                push x
                push dwSecoundOffsetBase
                call dwCallAddr
                popad
            }
        }
    }
}


void DllMainFrom::OnBnClickedPlantdp2()
{
    DWORD dwSecoundOffsetBase = *(DWORD*)(m_firstOffsetBase + 0x768);
    if (dwSecoundOffsetBase == NULL)
    {
        AfxMessageBox("请先进入游戏");
        return;
    }
    DWORD dwCallAddr = m_PlantsVsZombiesBase + 0xD120;

    for (size_t x = 0; x < 6; x++)
    {
        if (x % 2 != 0)
        {
            continue;
        }
        for (size_t y = 0; y < 6; y++)
        {
            __asm {
                pushad
                mov edx, 0xFFFFFFFF
                mov eax, 47
                push edx
                push eax
                mov eax, y
                push x
                push dwSecoundOffsetBase
                call dwCallAddr
                popad
            }
        }
    }
}

BOOL g_bQuitThread = FALSE;
DWORD WINAPI AutoBombThread1(LPVOID lpParam)
{
    DWORD dwfirstOffsetBase = (DWORD)lpParam;
    DWORD dwSecoundOffsetBase = *(DWORD*)(dwfirstOffsetBase + 0x768);
    DWORD dwFireCallAddr = (uintptr_t)GetModuleHandle(NULL) + 0x66D50;
    if (dwSecoundOffsetBase == NULL)
    {
        return 0;
    }

    while (g_bQuitThread)
    {
        // 轰炸次数
        DWORD dwCount = 2;

        // 获取地面种植数量
        DWORD dwPlantNumber = *(DWORD*)(dwSecoundOffsetBase + 0xB0);

        // 遍历玉米大炮
        DWORD dwThirdOffsetBase = *(DWORD*)(dwfirstOffsetBase + 0x320);
        dwThirdOffsetBase = *(DWORD*)(dwThirdOffsetBase + 0x88);
        dwThirdOffsetBase = *(DWORD*)(dwThirdOffsetBase + 0x1C);
        dwThirdOffsetBase = *(DWORD*)(dwThirdOffsetBase + 0xA8);
        for (int i = 0; i < dwPlantNumber && dwCount != 0; ++i)
        {
            // 植物指针
            auto dwPlantBase = dwThirdOffsetBase + i * 0x14c;
            // 植物种类
            DWORD dwPlantID = *(DWORD*)(dwPlantBase + 0x24);
            // 判断是否为玉米大炮
            if (dwPlantID != 47)
            {
                continue;
            }
            // 读取发射状态
            DWORD dwFireType = *(DWORD*)(dwPlantBase + 0x3C);
            // 判断是否已填充完毕
            if (dwFireType != 37)
            {
                continue;
            }

            DWORD dwX = 0;
            DWORD dwY = 600;
            static DWORD nMode = 1;
            if (nMode == 1)
            {
                dwX = 220;
                nMode = 2;
            }
            else
            {
                dwX = 480;
                nMode = 1;
            }
            __asm
            {
                pushad
                pushf
                mov eax, dwPlantBase
                mov esi, dwX
                mov ecx, dwY
                push esi
                push ecx
                call dwFireCallAddr
                popf
                popad
            }
            dwCount--;
        }

        Sleep(4000);
    }
    return 0;
}

DWORD WINAPI AutoBombThread2(LPVOID lpParam)
{
    DWORD dwfirstOffsetBase = (DWORD)lpParam;
    DWORD dwSecoundOffsetBase = *(DWORD*)(dwfirstOffsetBase + 0x768);
    if (dwSecoundOffsetBase == NULL)
    {
        return 0;
    }

    while (g_bQuitThread)
    {
        // 轰炸次数
        DWORD dwCount = 5;

        // 获取地面种植数量
        DWORD dwPlantNumber = *(DWORD*)(dwSecoundOffsetBase + 0xB0);

        // 遍历玉米大炮
        DWORD dwThirdOffsetBase = *(DWORD*)(dwfirstOffsetBase + 0x320);
        dwThirdOffsetBase = *(DWORD*)(dwThirdOffsetBase + 0x88);
        dwThirdOffsetBase = *(DWORD*)(dwThirdOffsetBase + 0x1C);
        dwThirdOffsetBase = *(DWORD*)(dwThirdOffsetBase + 0xA8);
        for (int i = 0; i < dwPlantNumber && dwCount != 0; ++i)
        {
            // 植物指针
            auto dwPlantBase = dwThirdOffsetBase + i * 0x14c;
            // 植物种类
            DWORD dwPlantID = *(DWORD*)(dwPlantBase + 0x24);
            // 判断是否为玉米大炮
            if (dwPlantID != 47)
            {
                continue;
            }

            *(DWORD*)(dwPlantBase + 0x90) = 2;
            *(DWORD*)(dwPlantBase + 0x80) = 600;
            static DWORD nMode = 5;
            switch (nMode)
            {
            case 0:
                *(DWORD*)(dwPlantBase + 0x84) = 220;
                nMode = 1;
                break;
            case 1:
                *(DWORD*)(dwPlantBase + 0x84) = 285;
                nMode = 2;
                break;
            case 2:
                *(DWORD*)(dwPlantBase + 0x84) = 350;
                nMode = 3;
                break;
            case 3:
                *(DWORD*)(dwPlantBase + 0x84) = 415;
                nMode = 4;
                break;
            case 4:
                *(DWORD*)(dwPlantBase + 0x84) = 480;
                nMode = 0;
                break;
            }
            dwCount--;
        }

        Sleep(1000);
    }
    return 0;
}

void DllMainFrom::OnBnClickedAutobomb1()
{
    m_bIsAutoBombMode1 = !m_bIsAutoBombMode1;
    if (m_bIsAutoBombMode1 == TRUE)
    {
        m_btnAutoBomb1.SetWindowText("玉米大炮普通模式轰炸[已开启]");
        m_btnAutoBomb2.EnableWindow(FALSE);
        g_bQuitThread = FALSE;
        if (m_hAutoBombThread1 != NULL)
        {
            WaitForSingleObject(m_hAutoBombThread1, INFINITE);
            CloseHandle(m_hAutoBombThread1);
            m_hAutoBombThread1 = NULL;
        }
        g_bQuitThread = TRUE;
        m_hAutoBombThread1 = CreateThread(NULL, 0, AutoBombThread1, (LPVOID)m_firstOffsetBase, NULL, NULL);
    }
    else
    {
        m_btnAutoBomb1.SetWindowText("玉米大炮普通模式轰炸[未开启]");
        m_btnAutoBomb2.EnableWindow(TRUE);
        g_bQuitThread = FALSE;
        if (m_hAutoBombThread1 != NULL)
        {
            WaitForSingleObject(m_hAutoBombThread1, INFINITE);
            CloseHandle(m_hAutoBombThread1);
            m_hAutoBombThread1 = NULL;
        }
    }
}


void DllMainFrom::OnBnClickedAutobomb2()
{
    m_bIsAutoBombMode2 = !m_bIsAutoBombMode2;
    if (m_bIsAutoBombMode2 == TRUE)
    {
        m_btnAutoBomb2.SetWindowText("玉米大炮变态模式轰炸[已开启]");
        m_btnAutoBomb1.EnableWindow(FALSE);
        g_bQuitThread = FALSE;
        if (m_hAutoBombThread2 != NULL)
        {
            WaitForSingleObject(m_hAutoBombThread2, INFINITE);
            CloseHandle(m_hAutoBombThread2);
            m_hAutoBombThread2 = NULL;
        }
        g_bQuitThread = TRUE;
        m_hAutoBombThread2 = CreateThread(NULL, 0, AutoBombThread2, (LPVOID)m_firstOffsetBase, NULL, NULL);
    }
    else
    {
        m_btnAutoBomb2.SetWindowText("玉米大炮变态模式轰炸[未开启]");
        m_btnAutoBomb1.EnableWindow(TRUE);
        g_bQuitThread = FALSE;
        if (m_hAutoBombThread2 != NULL)
        {
            WaitForSingleObject(m_hAutoBombThread2, INFINITE);
            CloseHandle(m_hAutoBombThread2);
            m_hAutoBombThread2 = NULL;
        }
    }
}

void DllMainFrom::OnBnClickedAutocollectsun()
{
    m_bIsAutoCollectSun = !m_bIsAutoCollectSun;
    LPBYTE lpAddr = (LPBYTE)(m_PlantsVsZombiesBase + 0x3158f);
    DWORD dwOldProctect = 0;
    if (!VirtualProtect(lpAddr, sizeof BYTE, PAGE_EXECUTE_READWRITE, &dwOldProctect))
    {
        AfxMessageBox("权限不足");
        return;
    }
    if (m_bIsAutoCollectSun)
    {
        m_btnAutoCollectSun.SetWindowText("自动收集阳光金币[已开启]");
        *(BYTE*)(m_PlantsVsZombiesBase + 0x3158f) = 0xEB;
    }
    else
    {
        m_btnAutoCollectSun.SetWindowText("自动收集阳光金币[未开启]");
        *(BYTE*)(m_PlantsVsZombiesBase + 0x3158f) = 0x75;
    }
    VirtualProtect(lpAddr, sizeof BYTE, dwOldProctect, &dwOldProctect);
}
