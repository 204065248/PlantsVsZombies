#pragma once
#include <afxdialogex.h>

// DllMainFrom 对话框

class DllMainFrom : public CDialogEx
{
	DECLARE_DYNAMIC(DllMainFrom)

public:
	DllMainFrom(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DllMainFrom();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DLG_MAINFROM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedSetSunnum();
    afx_msg void OnBnClickedPlant();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnBnClickedSetCardPlantCd();
    afx_msg void OnBnClickedSetPlantHealth();

    afx_msg void OnBnClickedPlantdp1();
    afx_msg void OnBnClickedPlantdp2();

    afx_msg void OnBnClickedAutobomb1();
    afx_msg void OnBnClickedAutobomb2();
    afx_msg void OnBnClickedAutocollectsun();

    void ShowSunNumber();
    void ShowCardInfo();
    void ShowPlantInfo();

    uintptr_t m_PlantsVsZombiesBase;
    uintptr_t m_firstOffsetBase;
	CEdit m_edtPlantID;
	CEdit m_edtPlantX;
	CEdit m_edtPlantY;
    CEdit m_edtPlantInfo;
    CEdit m_edtCardInfo;
    // 普通模式自动轰炸
    CButton m_btnAutoBomb1;
    // 变态模式自动轰炸
    CButton m_btnAutoBomb2;
    // 自动收集阳光
    CButton m_btnAutoCollectSun;

    BOOL m_bIsAutoBombMode1;
    BOOL m_bIsAutoBombMode2;
    HANDLE m_hAutoBombThread1;
    HANDLE m_hAutoBombThread2;

    BOOL m_bIsAutoCollectSun;
};
