// RsDecode.cpp: implementation of the RsDecode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RsDecode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*
���鳤��
sg0===npar
sg1===npar
sigma===npar/2+2
omega===npar/2+1
syn===npar
*/

RsDecode::RsDecode()
{
	m_galois = Galois();
}

RsDecode::~RsDecode()
{

}

RsDecode::RsDecode(int npar)
{
	m_galois = Galois();
	this->m_npar = npar;
}

/**
 * Modified Berlekamp-Massey
 *
 * @param sigma int[]
 *		��(z)��{�����С����npar/2 + 2�����I�򤬱�Ҫ
 * 		��0,��1,��2, ... ��<jisu>
 * @param omega int[]
 *		��(z)��{�����С����npar/2 + 1�����I�򤬱�Ҫ
 *		��0,��1,��2, ... ��<jisu-1>
 * @param syn int[]
 *		����ɥ��`������
 * 		s0,s1,s2, ... s<npar-1>
 * @return int
 * 		>= 0: �Ҥδ���
 * 		< 0: ����`
 */
int RsDecode::calcSigmaMBM(int * sigma, int * omega, int * syn)
{
	int * sg0 = new int[m_npar];
	int * sg1 = new int[m_npar];
	int i;
	for(i=0;i<m_npar;i++)
	{
		sg0[i]=0;sg1[i]=0;
	}
	sg0[1] = 1;
	sg1[0] = 1;
	int jisu0 = 1;
	int jisu1 = 0;
	int m = -1;

	for(int n = 0; n < m_npar; n++) 
	{
		// �Єeʽ��Ӌ��
		int d = syn[n];
		for(int i = 1; i <= jisu1; i++) 
		{
			d ^= m_galois.mul(sg1[i], syn[n - i]);
		}
		if(d != 0) 
		{
			int logd = m_galois.toLog(d);
			int * wk = new int[m_npar];
			for(i=0;i<m_npar;i++)
				wk[i]=0;
			for(int i = 0; i <= n; i++) 
			{
				wk[i] = sg1[i] ^ m_galois.mulExp(sg0[i], logd);
			}
			int js = n - m;
			if(js > jisu1) 
			{
				m = n - jisu1;
				jisu1 = js;
				if(jisu1 > m_npar / 2) 
				{
					delete [] wk;
					delete [] sg0;
					delete [] sg1;
					return -1;				// �Ҥδ�����npar / 2�򳬤����饨��`
				}
				for(int i = 0; i <= jisu0; i++) 
				{
					sg0[i] = m_galois.divExp(sg1[i], logd);
				}
				jisu0 = jisu1;
			}
		//	sg1 = wk;	//gy  �ĳ������
			for(i=0;i<m_npar;i++) //gy
			{ //gy
				sg1[i]=wk[i]; //gy
			} //gy
			delete [] wk;
		}

		int cnt=m_npar-1<jisu0 ? m_npar-1 : jisu0;
		for(i=cnt-1;i>=0;i--)
			sg0[i+1]=sg0[i];

		sg0[0] = 0;
		jisu0++;
	}
	m_galois.mulPoly(omega, sg1, syn, m_npar/2+1, m_npar, m_npar);

	int cnt=m_npar<m_npar/2+2 ? m_npar : m_npar/2+2;
	for(i=0;i<cnt;i++)
		sigma[i]=sg1[i];

	delete [] sg0;
	delete [] sg1;
	return jisu1;
}

/**
 * ������̽���ˤ���`��λ�ä�����
 *		��(z) = 0�ν��̽������
 *		��������̽���ϥǩ`���L���ڤν�Τߤ�
 *		jisu���ν⤬Ҋ�Ĥ���ʤ���С�����`�Ȥ���
 * @param pos int[]
 * 		�`��λ�ø�{�����С�jisu�����I�򤬱�Ҫ
 * @param n int
 * 		�ǩ`���L
 * @param jisu int
 * 		�Ҥδ���
 * @param sigma int[]
 * 		��0,��1,��2, ... ��<jisu>
 * @return int
 *		0: �����K��
 *		< 0: ����`
 */
int RsDecode::chienSearch(int * pos, int n, int jisu, int * sigma)
{
	/*
	 * ��(z) = (1-��^i*z)(1-��^j*z)(1-��^k*z)
	 *       = 1 + ��1z + ��2z^2 +...
	 * ��1 = ��^i + ��^j + ��^k
	 * ��ӛ�����|�����ä��ơ��ץ����m��
	 * last = ��1���顢Ҋ�Ĥ������Ρ��������Ƥ������Ȥˤ�ꡢ����ν��last�Ȥʤ�
	 */
	int last = sigma[1];

	if(jisu == 1) {
		// ������1�ʤ�С�last�����ν�Ǥ���
		if(m_galois.toLog(last) >= n) {
			return RS_CORRECT_ERROR;	// ������ʤΤǥ���`
		}
		pos[0] = last;
		return 0;
	}

	int posIdx = jisu - 1;		// �`��λ�ø�{�å���ǥå���
	for(int i = 0; i < n; i++) {
		/*
		 * ��(z)��Ӌ��
		 * w ��1(0�\���)�˳��ڻ������ᡢ�Ф���<1..jisu>�����
		 * z = 1/��^i = ��^I�Ȥ����
		 * ��(z) = 1 + ��1��^I + ��2(��^I)^2 + ��3(��^I)^3 + ... + ��<jisu>/(��^I)^<jisu>
		 *       = 1 + ��1��^I + ��2��^(I*2) + ��3��^(I*3) + ... + ��<jisu>��^(I*<jisu>)
		 */
		int z = 255 - i;					// z = 1/��^i�Υ�����`
		int wk = 1;
		for(int j = 1; j <= jisu; j++) {
			wk ^= m_galois.mulExp(sigma[j], (z * j) % 255);
		}
		if(wk == 0) {
			int pv = m_galois.toExp(i);		// ��(z) = 0�ν�
			last ^=  pv;					// last�����Ҋ�Ĥ��ä��������
			pos[posIdx--] = pv;
			if(posIdx == 0) {
				// �Ф꤬һ�Ĥʤ�С�last�����ν�Ǥ���
				if(m_galois.toLog(last) >= n) {
					return RS_CORRECT_ERROR;	// ����ν⤬������ʤΤǥ���`
				}
				pos[0] = last;
				return 0;
			}
		}
	}
	// ̽���ˤ��ǩ`���L���ڤˡ�jisu���ν⤬Ҋ�Ĥ���ʤ��ä�
	return RS_CORRECT_ERROR;
}

/**
 * Forney�����`��ӆ�����Ф�
 *		��(z) = (1-��^i*z)(1-��^j*z)(1-��^k*z)
 *		��'(z) = ��^i * (1-��^j*z)(1-��^k*z)...
 *			   + ��^j * (1-��^i*z)(1-��^k*z)...
 *			   + ��^k * (1-��^i*z)(1-��^j*z)...
 *		��(z) = (E^i/(1-��^i*z) + E^j/(1-��^j*z) + ...) * ��(z)
 *			  = E^i*(1-��^j*z)(1-��^k*z)...
 *			  + E^j*(1-��^i*z)(1-��^k*z)...
 *			  + E^k*(1-��^i*z)(1-��^j*z)...
 *		�� E^i = ��^i * ��(z) / ��'(z)
 * @param data int[]
 *		�����ǩ`������
 * @param length int
 *		�����ǩ`���L��
 * @param jisu int
 *		�Ҥδ���
 * @param pos int[]
 *		�`��λ������
 * @param sigma int[]
 *		��0,��1,��2, ... ��<jisu>
 * @param omega int[]
 *		��0,��1,��2, ... ��<jisu-1>
 */
void RsDecode::doForney(BYTE * data, int length, int jisu, int * pos, int * sigma, int * omega)
{
	int i,j;
	for(i = 0; i < jisu; i++)
	{
		int ps = pos[i];
		int zlog = 255 - m_galois.toLog(ps);					// z�Υ�����`

		// ��(z)��Ӌ��
		int ov = omega[0];
		for(j = 1; j < jisu; j++)
		{
			ov ^= m_galois.mulExp(omega[j], (zlog * j) % 255);		// ov += ��i * z^j
		}

		// ��'(z)�΂���Ӌ��(��(z)����ʽ��΢��)
		int dv = sigma[1];
		for(j = 2; j < jisu; j += 2)
		{
			dv ^= m_galois.mulExp(sigma[j + 1], (zlog * j) % 255);	// dv += ��<j+1> * z^j
		}

		/*
		 * �`��ӆ�� E^i = ��^i * ��(z) / ��'(z)
		 * �`��λ�äι���ϥ�����̽���ΤȤ��˱��^����Ƥ���Τǡ�
		 * �����Ǥϥ����å����ʤ�
		 */
		data[m_galois.toPos(length, ps)] ^= m_galois.mul(ps, m_galois.div(ov, dv));
	}
}

/**
 * RS���`�ɤΥǥ��`��
 *
 * @param data int[]
 *		�����ǩ`������
 * @param length int
 * 		�ѥ�ƥ��򺬤᤿�ǩ`���L
 * @param noCorrect boolean
 * 		�����å��Τߤ�ӆ�����Ф�ʤ�
 * @return int
 * 		0: ����`�ʤ�
 * 		> 0: ���ꂎ�����`���ӆ������
 * 		< 0: ӆ������
 */
int RsDecode::decode(BYTE * data, int length, boolean noCorrect)
{
	if(length < m_npar || length > 255) {
		return RS_PERM_ERROR;
	}
	int i;

	// ����ɥ��`���Ӌ��
	int * syn = new int[m_npar];
	for(i=0;i<m_npar;i++)syn[i]=0;

	if(m_galois.calcSyndrome(data, length, syn, m_npar)) {
		if(syn)
		{
			delete [] syn;
			syn=NULL;
		}
		return 0;		// ����`�o��
	}
	// ����ɥ��`����ҤȦؤ�����
	int * sigma = new int[m_npar/2+2];
	for(i=0;i<m_npar/2+2;i++)sigma[i]=0;
	int * omega = new int[m_npar/2+1];
	for(i=0;i<m_npar/2+1;i++)omega[i]=0;
	int jisu = calcSigmaMBM(sigma, omega, syn);
	if(jisu <= 0) 
	{
		if(syn)
		{
			delete [] syn;
			syn=NULL;
		}
		if(sigma)
		{
			delete [] sigma;
			sigma=NULL;
		}
		if(omega)
		{
			delete [] omega;
			omega=NULL;
		}
		return RS_CORRECT_ERROR;
	}
	// ������̽���ˤ���`��λ�ä�����
	int * pos = new int[jisu];
	for(i=0;i<jisu;i++)pos[i]=0;

	int r = chienSearch(pos, length, jisu, sigma);
	if(r < 0) {
		if(syn)
		{
			delete [] syn;
			syn=NULL;
		}
		if(sigma)
		{
			delete [] sigma;
			sigma=NULL;
		}
		if(omega)
		{
			delete [] omega;
			omega=NULL;
		}
		return r;
	}
	if(!noCorrect) {
		// �`��ӆ��
		doForney(data, length, jisu, pos, sigma, omega);
	}
	if(syn)
	{
		delete [] syn;
		syn=NULL;
	}
	if(sigma)
	{
		delete [] sigma;
		sigma=NULL;
	}
	if(omega)
	{
		delete [] omega;
		omega=NULL;
	}
	return jisu;
}

int RsDecode::decode(BYTE * data, int length)
{
	return decode(data, length, false);
}