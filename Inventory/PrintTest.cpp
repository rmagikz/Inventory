#include "Common.h"
#include <stdlib.h>

using namespace DYMO_Label_Framework;

int main() {
	CoInitialize(NULL);

	try
	{
		IFrameworkPtr framework(__uuidof(Framework));

		CString labelA = CString(_T("thelabel.label"));
		CString printerN = CString(_T("DYMO LabelWriter 450 Turbo"));
		//ILabelPtr label = framework->OpenLabel(_bstr_t(labelA));
		ILabelPtr label = framework->OpenLabel(L"thelabel.label");
		//IPrinterPtr printer = framework->GetLabelWriterPrinters()->GetItem(0);
		//IPrinterPtr printer = framework->GetPrinterByName(_bstr_t(printerN));
		IPrintParamsPtr printParams;
		ILabelWriterPrintParamsPtr labelWriterPrintParams(__uuidof(LabelWriterPrintParams));
		printParams = labelWriterPrintParams;
		labelWriterPrintParams->PutRollSelection(RollSelection_Auto);
		printParams->PutCopies(1);

		//label->Print(printer, printParams);
		framework->PrintLabel(L"DYMO LabelWriter 450 Turbo", L"", label->SaveToXml(), L"");
	}
	catch (_com_error& e)
	{
		_tprintf_s(_T("Com error was \"%s\", HRESULT 0x%X\n"), e.ErrorMessage(), e.Error());
	}
}
