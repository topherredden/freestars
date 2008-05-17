#include "FSClient.h"
#include "RaceBuild.h"

RaceBuild::RaceBuild(void)
	:Player(1)
{
}

RaceBuild::~RaceBuild(void)
{
}



wxString leftover_buy_Strings[] = {
    _("Nothing"),
    _("Surface minerals"),
    _("Mineral concentrations"),
    _("Mines"),
    _("Factories"),
    _("Defenses")
};

wxString tech_cost_Strings[] = {
    _("Costs 50% less"),
    _("Costs standard amount"),
    _("Costs 75% extra")
};

//original gravity string algorithm:
//char tmps[10];
//const char* gravityFromGravityPoints(int grav)
//{
//	int result, tmp = abs(grav-50);
//	if (tmp<=25) result = (tmp+25)*4;
//	else result = tmp*24-400;
//	if (grav<50) result = 10000/result;
//
//	sprintf(tmps,"%d.%02d",result/100,result%100);
//	return tmps;
//}

//i wanted gravity the values to begin differently... but so i got no algorithm ;)
wxString hab_0_value[] = 
{
	//	0		1		2		3		4		5		6		7		8		9	
	"0.08"	,"0.09"	,"0.10"	,"0.11"	,"0.12"	,"0.13"	,"0.14"	,"0.15"	,"0.16"	,"0.17"	//10
	,"0.18"	,"0.19"	,"0.2"	,"0.21"	,"0.22"	,"0.23"	,"0.24"	,"0.25"	,"0.27"	,"0.29"	//20
	,"0.31"	,"0.33"	,"0.36"	,"0.4"	,"0.44"	,"0.5"	,"0.51"	,"0.52"	,"0.53"	,"0.54"	//30
	,"0.55"	,"0.56"	,"0.58"	,"0.59"	,"0.6"	,"0.62"	,"0.64"	,"0.65"	,"0.67"	,"0.69"	//40
	,"0.71"	,"0.73"	,"0.75"	,"0.78"	,"0.8"	,"0.83"	,"0.86"	,"0.89"	,"0.92"	,"0.96"	//50
	,"1"	,"1.04"	,"1.08"	,"1.12"	,"1.16"	,"1.2"	,"1.24"	,"1.28"	,"1.32"	,"1.36"	//60
	,"1.4"	,"1.44"	,"1.48"	,"1.52"	,"1.56"	,"1.6"	,"1.64"	,"1.68"	,"1.72"	,"1.76"	//70
	,"1.8"	,"1.84"	,"1.88"	,"1.92"	,"1.96"	,"2"	,"2.24"	,"2.48"	,"2.72"	,"2.96"	//80
	,"3.2"	,"3.44"	,"3.68"	,"3.92"	,"4.16"	,"4.4"	,"4.64"	,"4.88"	,"5.12"	,"5.36"	//90
	,"5.6"	,"5.84"	,"6.08"	,"6.32"	,"6.56"	,"6,8"	,"7.04"	,"7.28"	,"7.52"	,"7.76"	//100
	,"8"
	//	1		2		3		4		5		6		7		8		9		10
};

wxString hab_unit[] =
{
	"g"	,"�C"	,"mR"	,"?"
};

short hab_colour[][3] =
{
	{0, 0, 128},	{128, 0, 0},	{0, 128, 0},	{128, 128, 0}
};

wxColour RaceBuild::GetHabColour(int hab) const
{
	return wxColour(hab_colour[hab][0],hab_colour[hab][1],hab_colour[hab][2]);
}

wxString RaceBuild::GetHabUnitString(int hab) const
{
	return hab_unit[hab];
}

wxString RaceBuild::GetFullHabString(int hab) const
{
	wxString str;
	str << FreeStars::Rules::GetHabName(hab).data() << ": ";
	if (HabWidth(hab) == -1)
		str << "N/A";
	else
		str << GetHabValueString(hab,HabCenter(hab)-HabWidth(hab)) 
			<< GetHabUnitString(hab)
			<< " to "
			<< GetHabValueString(hab,HabCenter(hab)+HabWidth(hab))
			<< GetHabUnitString(hab);
	return str;
}


wxString RaceBuild::GetHabValueString(int hab, int value) const
{
	wxString tmpstr;
	switch (hab)
	{
	case 0: //grav?
        return hab_0_value[value];
	case 1: //temp?
		tmpstr << (value-50)*4;
		return tmpstr;
	default:
		tmpstr << value;
		return tmpstr;
	}
}

const wxString * RaceBuild::GetLeftoverStrings() const
{
	return leftover_buy_Strings;
}

const wxString * RaceBuild::GetTechCostStrings() const
{
	return tech_cost_Strings;
}


long RaceBuild::GetIntTechCost(FreeStars::TechType tt) const
{
	long tcf = TechCostFactor(tt)*100;
	switch (tcf)
	{
	case 50: return 0;
	case 100: return 1;
	case 175: return 2;
	default: wxMessageBox("I dont know such tech cost :(","Sorry!");
			return 1;
	}
}

void RaceBuild::SetIntTechCost(FreeStars::TechType tt, long value)
{
	double newcost;
	switch (value)
	{
	case 0: newcost = 0.50; break;
	case 1: newcost = 1.00; break;
	case 2: newcost = 1.75; break;
	default: wxMessageBox("I dont know such tech cost :(","Sorry!");
			return;
	}
	mTechCostFactor[tt] = newcost;
}


void RaceBuild::AddLRT(const FreeStars::RacialTrait * lrt)
{
	deque<const FreeStars::RacialTrait *>::iterator what;
	for (what = mLRTs.begin();what != mLRTs.end();what++)
	{
		if (*what == lrt)
		{
			wxMessageBox("Cant add LRT what is already present.","Sorry!");
			return;
		}
	}
	mLRTs.push_back(lrt);
}

void RaceBuild::RemoveLRT(const FreeStars::RacialTrait * lrt)
{
	deque<const FreeStars::RacialTrait *>::iterator what;
	for (what = mLRTs.begin();what != mLRTs.end();what++)
	{
		if (*what == lrt)
		{
            mLRTs.erase(what);
			return;
		}
	}
	wxMessageBox("Cant remove LRT thats not present.","Sorry!");
}


void RaceBuild::WriteRaceFile(const char*location)
{
	TiXmlDocument doc;	
	doc.SetCondenseWhiteSpace(false);

	TiXmlDeclaration decl("1.0", "", "yes");
	doc.InsertEndChild(decl);

	TiXmlElement * RaceFile = new TiXmlElement("RaceDefinition");
	TiXmlComment * comment = new TiXmlComment();
	comment->SetValue("Generated by FreeStars Client");
	RaceFile->LinkEndChild(comment);

	TiXmlElement * MetaInfo = new TiXmlElement("MetaInfo");
	AddDouble(MetaInfo, "FreeStarsVersion", FreeStars::FREESTARSVERSION);
	AddDouble(MetaInfo, "FileVersion", FreeStars::HOSTFILEVERSION);
	RaceFile->LinkEndChild(MetaInfo);

	FreeStars::Rules::WriteRulesFile(RaceFile);

	AddString(RaceFile, "SingularName", mSingularName.c_str());
	AddString(RaceFile, "PluralName", mPluralName.c_str());
	AddString(RaceFile, "Password", mPassword.c_str());
	AddLong(RaceFile, "Randomize", FreeStars::Random(10000));
	AddLong(RaceFile, "RaceEmblem", mRaceEmblem);

	AddString(RaceFile, "PrimaryRacialTrait", mPRT->Name().c_str());

	deque<const FreeStars::RacialTrait *>::const_iterator rti;
	for (rti = mLRTs.begin(); rti != mLRTs.end(); ++rti) {
		if (!(*rti)->Name().empty())
			AddString(RaceFile, "LesserRacialTrait", (*rti)->Name().c_str());
	}

	WriteHabs(RaceFile);

	AddDouble(RaceFile, "GrowthRate", mGrowthRate);
	AddLong(RaceFile, "PopEfficiency", mPopEfficiency);
	AddLong(RaceFile, "FactoryRate", mFactoryRate);
	mFactoryCost.WriteCosts(RaceFile, "FactoryCost");
	AddLong(RaceFile, "FactoriesRun", mFactoriesRun);
	AddLong(RaceFile, "MineRate", mMineRate);
	mMineCost.WriteCosts(RaceFile, "MineCost");
	AddLong(RaceFile, "MinesRun", mMinesRun);


	RaceFile->LinkEndChild(FreeStars::Rules::WriteArrayFloat("TechFactor", mTechCostFactor, FreeStars::TECHS));

	if (mStartAt)
		AddString(RaceFile, "StartAt", "true");

	if (mLeftoverPoints > 0) 
	{
		switch (mLeftoverBuys) 
		{
		case FreeStars::LOPB_MINERALS:
			AddLong(RaceFile, "StartMinerals", mLeftoverPoints);
			break;
		case FreeStars::LOPB_CONCENTRATIONS:
			AddLong(RaceFile, "StartConcentrations", mLeftoverPoints);
			break;
		case FreeStars::LOPB_MINES:
			AddLong(RaceFile, "StartMines", mLeftoverPoints);
			break;
		case FreeStars::LOPB_FACTORIES:
			AddLong(RaceFile, "StartFactories", mLeftoverPoints);
			break;
		case FreeStars::LOPB_DEFENSES:
			AddLong(RaceFile, "StartDefneses", mLeftoverPoints);
			break;
		}
	}

	TiXmlElement * Settings = new TiXmlElement("InitialSettings");
	WriteBattlePlan(Settings, 0);
	RaceFile->LinkEndChild(Settings);

	doc.LinkEndChild(RaceFile);
	string File = location;
	doc.SaveFile(File);
}
