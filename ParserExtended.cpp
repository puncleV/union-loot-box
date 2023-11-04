// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
    int zCParser::GetScriptInt(zSTRING const& str, int index) {
        int retVal = 0;
        zCPar_Symbol* ps = GetSymbol(str);
        if (ps)
            ps->GetValue(retVal, index);
        else
            return -1;
        return retVal;

    };

    int zCParser::SetScriptInt(zSTRING const& str, int index, int value) {
        int retVal = 0;
        zCPar_Symbol* ps = GetSymbol(str);
        if (ps)
            ps->SetValue(value, index);
        else
            return -1;
        return retVal;

    };
}