#pragma once
#include <bitset>
#include <iostream>
#include <vector>
#include "fft.h"
#include "type.h"
#include "wave-processor.h"

extern const int NumBinsInFftWinM; // 2048
extern const int NumSamplesPerFrameM; //1850
const double frameInterval = 0.37;
const int sampleRate = 5000;

extern double duration_FFT;

class FingerExtractor {
public:
	FingerExtractor() :_wp(5000){};
	~FingerExtractor();
	void CalcFingerprint(const string waveFilePath);
	int PrintFingerToFile(const string filepath);
	void GetQueryFinger(FingerItem* new_finger, int& size);
	int GetFingerFileId();
	void OutputTrainingSamples(const std::string& x_path,
		const std::string& y_path);
	//vector<short> _get_top_N(vector<double>& energy);

private:
	void _CalcFreqBind();
	int _SelectBind(double point_freq);
	int _MultiThreadFFT(int thread_num, int frame_size, int frame_index[FFT_THREAD]);
	int _Energying(long all_time_data_size);
	void _Fingerprinting();

	WaveProcessor _wp;
	string _wavepath;
	int _frame_num; //��¼���������Ƶһ���ж���֡
	short _all_time_data[SamplesVectorSize]; // for query
	double _energy[SUB_FINGER_NUM][33]; //����E[n,m]����ʾ��n֡�ĵ�m��Ƶ��������ֵ
	char _fingers[SUB_FINGER_NUM][32]; //���յ�ָ�ƽ��
	std::vector<std::vector<double>> _log_power; // The second demension is 2048.
};