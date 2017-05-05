#include "bigdivint.h"

#include "gtest/gtest.h"

TEST(DivideTest, ByZero) {
  BigDivInt val1("989247982478213874973248237421498749821743981742");
  BigDivInt val1_(0);
  ASSERT_THROW(val1 / val1_, BigException);

  BigDivInt val2(0);
  BigDivInt val2_(0);
  ASSERT_THROW(val2 / val2_, BigException);
}

TEST(DivideTest, SameSign) {
  BigDivInt val1("234734382764873264873264872648732684632874268746873264");
  BigDivInt val1_("984325948325875984327457984327598432759843275798432757984327598432759843275093275");
  BigDivInt quot1_expected(0);
  BigDivInt quot1 = val1 / val1_;
  ASSERT_EQ(quot1_expected, quot1);

  BigDivInt val2("987345798347598327598743259874325987439857432859432759843275983274958743298574329574329875943875943275932745984327598743598743298759832475983275983275");
  BigDivInt val2_("9748327483274983273268758325794");
  BigDivInt quot2_expected("101283609936326862010691846217282730590501763236494210794126819473345411238449140734789136981629239161966629378598752705");
  BigDivInt quot2 = val2 / val2_;
  ASSERT_EQ(quot2_expected, quot2);

  BigDivInt val3("-4358743258743268638753294365874326587432658743265873246587432597432658743258743263872687564323874658743265874326587432658743265874326554872658743254774748837474");
  BigDivInt val3_("-9889389532874958439875874359827957984791879127498274987249872987497428245798432875983247598732758475932579492345");
  BigDivInt quot3_expected("440749476421537236347926847348877273773987493465");
  BigDivInt quot3 = val3 / val3_;
  ASSERT_EQ(quot3_expected, quot3);
}

TEST(DivideTest, DiffSign) {
  BigDivInt val1("234734382764873264873264872648732684632874268746873264");
  BigDivInt val1_("-984325948325875984327457984327598432759843275798432757984327598432759843275093275");
  BigDivInt quot1_expected(-1);
  BigDivInt quot1 = val1 / val1_;
  ASSERT_EQ(quot1_expected, quot1);

  BigDivInt val2("-987345798347598327598743259874325987439857432859432759843275983274958743298574329574329875943875943275932745984327598743598743298759832475983275983275");
  BigDivInt val2_("97483274832749832732687583257940043958438543285245852543254235425243");
  BigDivInt quot2_expected("-10128360993632686201069184621728268491836620493922169812391852288665831041315421483");
  BigDivInt quot2 = val2 / val2_;
  ASSERT_EQ(quot2_expected, quot2);

  BigDivInt val3("+4358743258743268638753294365874326587432658743265873246587432597432658743258743263872687564323874658743265874326587432658743265874326554872658743254774748837474");
  BigDivInt val3_("-9889389532874958439875874359827957984791879127498274987249872987497428245798432875983247598732758475932579492345");
  BigDivInt quot3_expected("-440749476421537236347926847348877273773987493466");
  BigDivInt quot3 = val3 / val3_;
  ASSERT_EQ(quot3_expected, quot3);
}

TEST(DivideTest, DivideAndAssign) {
  BigDivInt val1("234734382764873264873264872648732684632874268746873264");
  BigDivInt val1_("-984325948325875984327457984327598432759843275798432757984327598432759843275093275");
  BigDivInt quot1_expected(-1);
  val1 /= val1_;
  ASSERT_EQ(quot1_expected, val1);

  BigDivInt val2("987345798347598327598743259874325987439857432859432759843275983274958743298574329574329875943875943275932745984327598743598743298759832475983275983275");
  BigDivInt val2_("97483274832749832732687583257940043958438543285245852543254235425243");
  BigDivInt quot2_expected("10128360993632686201069184621728268491836620493922169812391852288665831041315421482");
  val2 /= val2_;
  ASSERT_EQ(quot2_expected, val2);

  BigDivInt val3("+4358743258743268638753294365874326587432658743265873246587432597432658743258743263872687564323874658743265874326587432658743265874326554872658743254774748837474");
  BigDivInt val3_("-9889389532874958439875874359827957984791879127498274987249872987497428245798432875983247598732758475932579492345");
  BigDivInt quot3_expected("-440749476421537236347926847348877273773987493466");
  val3 /= val3_;
  ASSERT_EQ(quot3_expected, val3);
}

TEST(ModuloTest, SameSign) {
  BigDivInt val1("234734382764873264873264872648732684632874268746873264");
  BigDivInt val1_("984325948325875984327457984327598432759843275798432757984327598432759843275093275");
  BigDivInt r1_expected("234734382764873264873264872648732684632874268746873264");
  BigDivInt r1 = val1 % val1_;
  ASSERT_EQ(r1_expected, r1);

  BigDivInt val2("987345798347598327598743259874325987439857432859432759843275983274958743298574329574329875943875943275932745984327598743598743298759832475983275983275");
  BigDivInt val2_("97483274832749832732687583257940043958438543285245852543254235425243");
  BigDivInt r2_expected("56578355781481249445861045624989092593449760148380488067413228713149");
  BigDivInt r2 = val2 % val2_;
  ASSERT_EQ(r2_expected, r2);

  BigDivInt val3("-4358743258743268638753294365874326587432658743265873246587432597432658743258743263872687564323874658743265874326587432658743265874326554872658743254774748837474");
  BigDivInt val3_("-9889389532874958439875874359827957984791879127498274987249872987497428245798432875983247598732758475932579492345");
  BigDivInt r3_expected("-8161905011343875816511225996326197293761091593954485145908638753777142504593000981227760340320038457806043812049");
  BigDivInt r3 = val3 % val3_;
  ASSERT_EQ(r3_expected, r3);
}

TEST(ModuloTest, DiffSign) {
  BigDivInt val1("234734382764873264873264872648732684632874268746873264");
  BigDivInt val1_("-984325948325875984327457984327598432759843275798432757984327598432759843275093275");
  BigDivInt r1_expected("-984325948325875984327457984092864049994970010925167885335594913799885574528220011");
  BigDivInt r1 = val1 % val1_;
  ASSERT_EQ(r1_expected, r1);

  BigDivInt val2("-987345798347598327598743259874325987439857432859432759843275983274958743298574329574329875943875943275932745984327598743598743298759832475983275983275");
  BigDivInt val2_("97483274832749832732687583257940043958438543285245852543254235425243");
  BigDivInt r2_expected("40904919051268583286826537632950951364988783136865364475841006712094");
  BigDivInt r2 = val2 % val2_;
  ASSERT_EQ(r2_expected, r2);

  BigDivInt val3("+4358743258743268638753294365874326587432658743265873246587432597432658743258743263872687564323874658743265874326587432658743265874326554872658743254774748837474");
  BigDivInt val3_("-9889389532874958439875874359827957984791879127498274987249872987497428245798432875983247598732758475932579492345");
  BigDivInt r3_expected("-1727484521531082623364648363501760691030787533543789841341234233720285741205431894755487258412720018126535680296");
  BigDivInt r3 = val3 % val3_;
  ASSERT_EQ(r3_expected, r3);
}

TEST(ModuloTest, ModuloAndAssign) {
  BigDivInt val1("234734382764873264873264872648732684632874268746873264");
  BigDivInt val1_("984325948325875984327457984327598432759843275798432757984327598432759843275093275");
  BigDivInt r1_expected("234734382764873264873264872648732684632874268746873264");
  val1 %= val1_;
  ASSERT_EQ(r1_expected, val1);

  BigDivInt val2("-987345798347598327598743259874325987439857432859432759843275983274958743298574329574329875943875943275932745984327598743598743298759832475983275983275");
  BigDivInt val2_("97483274832749832732687583257940043958438543285245852543254235425243");
  BigDivInt r2_expected("40904919051268583286826537632950951364988783136865364475841006712094");
  val2 %= val2_;
  ASSERT_EQ(r2_expected, val2);

  BigDivInt val3("-4358743258743268638753294365874326587432658743265873246587432597432658743258743263872687564323874658743265874326587432658743265874326554872658743254774748837474");
  BigDivInt val3_("-9889389532874958439875874359827957984791879127498274987249872987497428245798432875983247598732758475932579492345");
  BigDivInt r3_expected("-8161905011343875816511225996326197293761091593954485145908638753777142504593000981227760340320038457806043812049");
  val3 %= val3_;
  ASSERT_EQ(r3_expected, val3);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
