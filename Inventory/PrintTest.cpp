#include "Common.h"
#include <stdlib.h>

using namespace DYMO_Label_Framework;

int main() {
	CoInitialize(NULL);

	try
	{
		IFrameworkPtr framework(__uuidof(Framework));

		CString labelA = CString(_T("19mm.label"));
		ILabelPtr label = framework->OpenLabel(_bstr_t(labelA));
		IPrinterPtr printer = framework->GetLabelWriterPrinters()->GetItem(0);
		IPrintParamsPtr printParams;
		ILabelWriterPrintParamsPtr labelWriterPrintParams(__uuidof(LabelWriterPrintParams));
		printParams = labelWriterPrintParams;
		labelWriterPrintParams->PutRollSelection(RollSelection_Auto);

		label->Print(printer, printParams);
	}
	catch (_com_error& e)
	{
		_tprintf_s(_T("Com error was \"%s\", HRESULT 0x%X\n"), e.ErrorMessage(), e.Error());
	}
}
