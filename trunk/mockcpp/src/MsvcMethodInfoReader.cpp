
#include <mockcpp/mockcpp.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/MsvcMethodInfoReader.h>
#include <mockcpp/OutputStringStream.h>

MOCKCPP_NS_START

namespace
{
   struct StupidInterface
   {
	   virtual void m0() = 0;
	   virtual void m1() = 0;
	   virtual void m2() = 0;
	   virtual void m3() = 0;
	   virtual void m4() = 0;
	   virtual void m5() = 0;
	   virtual void m6() = 0;
	   virtual void m7() = 0;
	   virtual void m8() = 0;
	   virtual void m9() = 0;
	   
	   virtual void m10() = 0;
	   virtual void m11() = 0;
	   virtual void m12() = 0;
	   virtual void m13() = 0;
	   virtual void m14() = 0;
	   virtual void m15() = 0;
	   virtual void m16() = 0;
	   virtual void m17() = 0;
	   virtual void m18() = 0;
	   virtual void m19() = 0;

	   virtual void m20() = 0;
	   virtual void m21() = 0;
	   virtual void m22() = 0;
	   virtual void m23() = 0;
	   virtual void m24() = 0;
	   virtual void m25() = 0;
	   virtual void m26() = 0;
	   virtual void m27() = 0;
	   virtual void m28() = 0;
	   virtual void m29() = 0;

	   virtual void m30() = 0;
	   virtual void m31() = 0;
	   virtual void m32() = 0;
	   virtual void m33() = 0;
	   virtual void m34() = 0;
	   virtual void m35() = 0;
	   virtual void m36() = 0;
	   virtual void m37() = 0;
	   virtual void m38() = 0;
	   virtual void m39() = 0;

	   virtual void m40() = 0;
	   virtual void m41() = 0;
	   virtual void m42() = 0;
	   virtual void m43() = 0;
	   virtual void m44() = 0;
	   virtual void m45() = 0;
	   virtual void m46() = 0;
	   virtual void m47() = 0;
	   virtual void m48() = 0;
	   virtual void m49() = 0;

	   virtual void m50() = 0;
	   virtual void m51() = 0;
	   virtual void m52() = 0;
	   virtual void m53() = 0;
	   virtual void m54() = 0;
	   virtual void m55() = 0;
	   virtual void m56() = 0;
	   virtual void m57() = 0;
	   virtual void m58() = 0;
	   virtual void m59() = 0;

	   virtual void m60() = 0;
	   virtual void m61() = 0;
	   virtual void m62() = 0;
	   virtual void m63() = 0;
	   virtual void m64() = 0;
	   virtual void m65() = 0;
	   virtual void m66() = 0;
	   virtual void m67() = 0;
	   virtual void m68() = 0;
	   virtual void m69() = 0;

	   virtual void m70() = 0;
	   virtual void m71() = 0;
	   virtual void m72() = 0;
	   virtual void m73() = 0;
	   virtual void m74() = 0;
	   virtual void m75() = 0;
	   virtual void m76() = 0;
	   virtual void m77() = 0;
	   virtual void m78() = 0;
	   virtual void m79() = 0;

	   virtual void m80() = 0;
	   virtual void m81() = 0;
	   virtual void m82() = 0;
	   virtual void m83() = 0;
	   virtual void m84() = 0;
	   virtual void m85() = 0;
	   virtual void m86() = 0;
	   virtual void m87() = 0;
	   virtual void m88() = 0;
	   virtual void m89() = 0;

	   virtual void m90() = 0;
	   virtual void m91() = 0;
	   virtual void m92() = 0;
	   virtual void m93() = 0;
	   virtual void m94() = 0;
	   virtual void m95() = 0;
	   virtual void m96() = 0;
	   virtual void m97() = 0;
	   virtual void m98() = 0;
	   virtual void m99() = 0;

   };
};

#define MOCKCPP_MSVC_GETADDROFMETHOD(N) \
case N: \
	return msvcGetAddrOfMethodOnly(&StupidInterface::m##N)


static void* MsvnGetAddressOfVirtualFunction(unsigned int index)
{
	switch(index)
	{
		MOCKCPP_MSVC_GETADDROFMETHOD(0);
		MOCKCPP_MSVC_GETADDROFMETHOD(1);
		MOCKCPP_MSVC_GETADDROFMETHOD(2);
		MOCKCPP_MSVC_GETADDROFMETHOD(3);
		MOCKCPP_MSVC_GETADDROFMETHOD(4);
		MOCKCPP_MSVC_GETADDROFMETHOD(5);
		MOCKCPP_MSVC_GETADDROFMETHOD(6);
		MOCKCPP_MSVC_GETADDROFMETHOD(7);
		MOCKCPP_MSVC_GETADDROFMETHOD(8);
		MOCKCPP_MSVC_GETADDROFMETHOD(9);

		MOCKCPP_MSVC_GETADDROFMETHOD(10);
		MOCKCPP_MSVC_GETADDROFMETHOD(11);
		MOCKCPP_MSVC_GETADDROFMETHOD(12);
		MOCKCPP_MSVC_GETADDROFMETHOD(13);
		MOCKCPP_MSVC_GETADDROFMETHOD(14);
		MOCKCPP_MSVC_GETADDROFMETHOD(15);
		MOCKCPP_MSVC_GETADDROFMETHOD(16);
		MOCKCPP_MSVC_GETADDROFMETHOD(17);
		MOCKCPP_MSVC_GETADDROFMETHOD(18);
		MOCKCPP_MSVC_GETADDROFMETHOD(19);

		MOCKCPP_MSVC_GETADDROFMETHOD(20);
		MOCKCPP_MSVC_GETADDROFMETHOD(21);
		MOCKCPP_MSVC_GETADDROFMETHOD(22);
		MOCKCPP_MSVC_GETADDROFMETHOD(23);
		MOCKCPP_MSVC_GETADDROFMETHOD(24);
		MOCKCPP_MSVC_GETADDROFMETHOD(25);
		MOCKCPP_MSVC_GETADDROFMETHOD(26);
		MOCKCPP_MSVC_GETADDROFMETHOD(27);
		MOCKCPP_MSVC_GETADDROFMETHOD(28);
		MOCKCPP_MSVC_GETADDROFMETHOD(29);

		MOCKCPP_MSVC_GETADDROFMETHOD(30);
		MOCKCPP_MSVC_GETADDROFMETHOD(31);
		MOCKCPP_MSVC_GETADDROFMETHOD(32);
		MOCKCPP_MSVC_GETADDROFMETHOD(33);
		MOCKCPP_MSVC_GETADDROFMETHOD(34);
		MOCKCPP_MSVC_GETADDROFMETHOD(35);
		MOCKCPP_MSVC_GETADDROFMETHOD(36);
		MOCKCPP_MSVC_GETADDROFMETHOD(37);
		MOCKCPP_MSVC_GETADDROFMETHOD(38);
		MOCKCPP_MSVC_GETADDROFMETHOD(39);

		MOCKCPP_MSVC_GETADDROFMETHOD(40);
		MOCKCPP_MSVC_GETADDROFMETHOD(41);
		MOCKCPP_MSVC_GETADDROFMETHOD(42);
		MOCKCPP_MSVC_GETADDROFMETHOD(43);
		MOCKCPP_MSVC_GETADDROFMETHOD(44);
		MOCKCPP_MSVC_GETADDROFMETHOD(45);
		MOCKCPP_MSVC_GETADDROFMETHOD(46);
		MOCKCPP_MSVC_GETADDROFMETHOD(47);
		MOCKCPP_MSVC_GETADDROFMETHOD(48);
		MOCKCPP_MSVC_GETADDROFMETHOD(49);

		MOCKCPP_MSVC_GETADDROFMETHOD(50);
		MOCKCPP_MSVC_GETADDROFMETHOD(51);
		MOCKCPP_MSVC_GETADDROFMETHOD(52);
		MOCKCPP_MSVC_GETADDROFMETHOD(53);
		MOCKCPP_MSVC_GETADDROFMETHOD(54);
		MOCKCPP_MSVC_GETADDROFMETHOD(55);
		MOCKCPP_MSVC_GETADDROFMETHOD(56);
		MOCKCPP_MSVC_GETADDROFMETHOD(57);
		MOCKCPP_MSVC_GETADDROFMETHOD(58);
		MOCKCPP_MSVC_GETADDROFMETHOD(59);

		MOCKCPP_MSVC_GETADDROFMETHOD(60);
		MOCKCPP_MSVC_GETADDROFMETHOD(61);
		MOCKCPP_MSVC_GETADDROFMETHOD(62);
		MOCKCPP_MSVC_GETADDROFMETHOD(63);
		MOCKCPP_MSVC_GETADDROFMETHOD(64);
		MOCKCPP_MSVC_GETADDROFMETHOD(65);
		MOCKCPP_MSVC_GETADDROFMETHOD(66);
		MOCKCPP_MSVC_GETADDROFMETHOD(67);
		MOCKCPP_MSVC_GETADDROFMETHOD(68);
		MOCKCPP_MSVC_GETADDROFMETHOD(69);

		MOCKCPP_MSVC_GETADDROFMETHOD(70);
		MOCKCPP_MSVC_GETADDROFMETHOD(71);
		MOCKCPP_MSVC_GETADDROFMETHOD(72);
		MOCKCPP_MSVC_GETADDROFMETHOD(73);
		MOCKCPP_MSVC_GETADDROFMETHOD(74);
		MOCKCPP_MSVC_GETADDROFMETHOD(75);
		MOCKCPP_MSVC_GETADDROFMETHOD(76);
		MOCKCPP_MSVC_GETADDROFMETHOD(77);
		MOCKCPP_MSVC_GETADDROFMETHOD(78);
		MOCKCPP_MSVC_GETADDROFMETHOD(79);

		MOCKCPP_MSVC_GETADDROFMETHOD(80);
		MOCKCPP_MSVC_GETADDROFMETHOD(81);
		MOCKCPP_MSVC_GETADDROFMETHOD(82);
		MOCKCPP_MSVC_GETADDROFMETHOD(83);
		MOCKCPP_MSVC_GETADDROFMETHOD(84);
		MOCKCPP_MSVC_GETADDROFMETHOD(85);
		MOCKCPP_MSVC_GETADDROFMETHOD(86);
		MOCKCPP_MSVC_GETADDROFMETHOD(87);
		MOCKCPP_MSVC_GETADDROFMETHOD(88);
		MOCKCPP_MSVC_GETADDROFMETHOD(89);

		MOCKCPP_MSVC_GETADDROFMETHOD(90);
		MOCKCPP_MSVC_GETADDROFMETHOD(91);
		MOCKCPP_MSVC_GETADDROFMETHOD(92);
		MOCKCPP_MSVC_GETADDROFMETHOD(93);
		MOCKCPP_MSVC_GETADDROFMETHOD(94);
		MOCKCPP_MSVC_GETADDROFMETHOD(95);
		MOCKCPP_MSVC_GETADDROFMETHOD(96);
		MOCKCPP_MSVC_GETADDROFMETHOD(97);
		MOCKCPP_MSVC_GETADDROFMETHOD(98);
		MOCKCPP_MSVC_GETADDROFMETHOD(99);
	default:
		// TODO:
	   oss_t oss; oss << "BUG " << index;
	   MOCKCPP_FAIL(oss.str());
	}
	return 0;
}

unsigned int msvcGetIndexOfVirtualMethod(void* p)
{
	for(unsigned int i=0; i<100; i++)
	{
		if(MsvnGetAddressOfVirtualFunction(i) == p)
			return i;
	}
	// TODO:
	MOCKCPP_FAIL("it's too large");
	return 0;
}

void msvcVerifyNonVirtualMethod(void* p)
{
	for(unsigned int i=0; i<100; i++)
	{
		if(MsvnGetAddressOfVirtualFunction(i) == p)
		{
			// TODO:
			MOCKCPP_FAIL("Non Virtual");
		}
	}
}

MOCKCPP_NS_END
