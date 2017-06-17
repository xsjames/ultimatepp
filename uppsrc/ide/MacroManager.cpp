#include "ide.h"

#define METHOD_NAME "MacroManagerWindow " << UPP_FUNCTION_NAME << "(): "

static const int GLOBAL_MACRO_KEY = 0;
static const int LOCAL_MACRO_KEY  = 10;

MacroManagerWindow::MacroManagerWindow(Ide& ide)
	: ide(ide)
{
	CtrlLayout(*this, t_("Macro Manager"));
	Zoomable().Sizeable().MinimizeBox(false);
	macrosTree.NoRoot();
	
	parent.Add(editor.SizePos());
	parent.AddFrame(splitter.Left(macrosTree, 300));

	editor.Highlight("usc");
	editor.SetReadOnly();

	editButton.Disable();
	exportButton.Disable();
	
	LoadMacros();
	macrosTree.OpenDeep(0);
	editor.Hide();
	
	macrosTree.WhenSel = [=]           { OnMacroSel(); };
	macrosTree.WhenBar = [=](Bar& bar) { OnMacroBar(bar); };
	
	InitButtons();
}

void MacroManagerWindow::OnMacroBar(Bar& bar)
{
	bool isGlobalFile = IsString(macrosTree.Get());
	
	bar.Add(t_("New global macro file.."), [=]{ OnNewMacroFile();});
	bar.Add(t_("Delete macro file"),       [=]{ OnDeleteMacroFile();})
	    .Enable(isGlobalFile);

}

void MacroManagerWindow::InitButtons()
{
	closeButton.Tip(t_("Close macro manager."));
	editButton.Tip(t_("Edit selected element inside TheIDE."));
	importButton.Tip(t_("Import macro from .usc file to your global macros store."));
	exportButton.Tip(t_("Export current selected element. If macro or function is selected the parent file will be exported."));
	
	closeButton.Close();
	
	closeButton  << [=] { Break(); };
	editButton   << [=] { OnEditFile(); };
	importButton <<	[=] { OnImport(); };
	exportButton <<	[=] { OnExport(); };
}

void MacroManagerWindow::Layout()
{
	OnMacroSel();
}

void MacroManagerWindow::OnMacroSel()
{
	if(!macrosTree.IsCursor()) {
		editor.Hide();
		editButton.Disable();
		exportButton.Disable();
		return;
	}

	Value key = macrosTree.Get();
	if(IsNumber(key)) {
		editor.Hide();
		editButton.Disable();
		
		int node = macrosTree.Find(key);
		exportButton.Enable(macrosTree.GetChildCount(node) > 0);
		
		return;
	}

	if(IsString(key)) {
		editButton.Enable();
		exportButton.Disable();
		editor.Show();
		editor.Set(LoadFile(AppendFileName(GetLocalDir(),  (String)key)));
		
		return;
	}

	MacroElement element = ValueTo<MacroElement>(key);

	String macroContent = TrimBoth(element.comment);
	if(macroContent.GetCount())
		macroContent << "\n";

	macroContent << element.prototype <<  element.code;

	editButton.Enable();
	exportButton.Disable();
	editor.Show();
	editor.Set(macroContent);
}

void MacroManagerWindow::OnImport()
{
	String filePath = SelectFileOpen("*.usc");
	if(IsNull(filePath))
		return;
	
	if(!UscFileParser(filePath).IsValid()) {
		ErrorOK(DeQtf(String(t_("Import failed! Following file")) << " \"" << filePath << "\" " << t_("is not a valid macro file!")));
		return;
	}
	
	String localDir = GetLocalDir();
	if(!DirectoryExists(localDir) && !RealizeDirectory(localDir)) {
		ErrorOK(DeQtf(String(t_("Realizing directory")) << " \"" << localDir << "\" " << t_("failed.")));
		return;
	}
	
	String newFileName = GetFileName(filePath);
	String newFilePath = LocalPath(newFileName);
	if(FileExists(newFilePath) && !PromptYesNo(DeQtf(GenFileOverrideMessage(newFileName))))
		return;
	
	FileCopy(filePath, newFilePath);
	ReloadGlobalMacros();
	OnMacroSel();
}

void MacroManagerWindow::ExportFiles(Index<String>& files, const String& dir)
{
	for(const String& file : files) {
		String fileName = GetFileName(file);
		String filePath = AppendFileName(dir, GetFileName(file));
		
		if(FileExists(filePath) && !PromptYesNo(DeQtf(GenFileOverrideMessage(fileName))))
			continue;
		
		FileCopy(file, filePath);
	}
}

void MacroManagerWindow::FindNodeFiles(int id, Index<String>& list)
{
	Value key = macrosTree.Get(id);
	if(IsNumber(key) || IsString(key)) {
		for(int i = 0; i < macrosTree.GetChildCount(id); i++) {
			int node = macrosTree.GetChild(id, i);
			FindNodeFiles(node, list);
		}
	}
	else {
		MacroElement element = ValueTo<MacroElement>(key);
		list.FindAdd(element.fileName);
	}
}

void MacroManagerWindow::OnExport()
{
	if(!macrosTree.IsCursor())
		return;
	
	String dir = SelectDirectory();
	if(dir.IsEmpty())
		return;

	Value key = macrosTree.Get();
	if(IsNumber(key) || IsString(key)) {
		int id = macrosTree.GetCursor();
		Index<String> list;
		FindNodeFiles(id, list);
		ExportFiles(list, dir);
	}
}

void MacroManagerWindow::OnEditFile()
{
	if(!macrosTree.IsCursor())
		return;

	Value key = macrosTree.Get();
	if(IsNumber(key))
		return;
	
	// TODO: Move this logic outside class - we serious don't want ide dependency here.
	if(IsString(key)) {
		ide.EditFile(AppendFileName(GetLocalDir(), (String)key));
		ide.editor.SetCursor(0);
		ide.editor.CenterCursor();
	} else {
		MacroElement element = ValueTo<MacroElement>(key);
	
		ide.EditFile(element.fileName);
		ide.editor.SetCursor(ide.editor.GetPos(element.line - 1));
		ide.editor.CenterCursor();
	}
	
	Break();
}

void MacroManagerWindow::OnNewMacroFile()
{
	String fileName;
	if(!EditTextNotNull(fileName, t_("New global macro file"), t_("Macro file name:")))
		return;
	
	if(!fileName.EndsWith(".usc"))
		fileName << ".usc";
	
	String fullPath = AppendFileName(GetLocalDir(), fileName);
	if(FileExists(fullPath)) {
		PromptOK(String() << t_("file") << " \"" << fileName << "\" " << t_("already exists!"));
		return;
	}
	
	SaveFile(fullPath, "macro \"\" {}");
	ReloadGlobalMacros();
	
	macrosTree.FindSetCursor(fileName);
}

void MacroManagerWindow::OnDeleteMacroFile()
{
	String fileName = static_cast<String>(macrosTree.GetValue());
	if(!PromptOKCancel(t_("Are you sure you want to remove followin macro file \"" + fileName + "\"?"))) {
		return;
	}
	
	FileDelete(AppendFileName(GetLocalDir(), fileName));
	macrosTree.Remove(macrosTree.GetCursor());
}

String MacroManagerWindow::GenFileOverrideMessage(const String& fileName)
{
	return String(t_("Target file")) << " \"" << fileName << "\" " << t_("already exists! Do you want to overwrite it?");
}

void MacroManagerWindow::LoadUscDir(const String& dir, int globalNode)
{
	for(FindFile ff(AppendFileName(dir, "*.usc")); ff; ff.Next()) {
		String fileTitle = ff.GetName();
		if(!ff.GetPath().EndsWith(String() << "UppLocal" << DIR_SEPS << ff.GetName()))
			fileTitle = "../" + fileTitle;
		
		int fileNode = macrosTree.Add(globalNode, Image(), fileTitle, fileTitle);
		
		auto list = UscFileParser(ff.GetPath()).Parse();
		for(const auto& element : list) {
			macrosTree.Add(fileNode, element.GetImage(), RawToValue(element), element.name);
		}
	}
}

void MacroManagerWindow::LoadMacros()
{
	ReloadGlobalMacros();
	ReloadLocalMacros();
}

void MacroManagerWindow::ReloadGlobalMacros()
{
	int globalNode = macrosTree.Find(0);
	if(globalNode < 0) {
		globalNode = macrosTree.Add(0, Image(), GLOBAL_MACRO_KEY, t_("Global macros"));
	}
	else {
		macrosTree.RemoveChildren(globalNode);
	}

	LoadUscDir(GetLocalDir(), globalNode);
	LoadUscDir(GetFileFolder(ConfigFile("x")), globalNode);
	
	macrosTree.OpenDeep(0);
}

void MacroManagerWindow::ReloadLocalMacros()
{
	int localNode = macrosTree.Add(0, Image(), LOCAL_MACRO_KEY, t_("Local macros"));

	const Workspace& wspc = ide.IdeWorkspace();

	for(int i = 0; i < wspc.GetCount(); i++) {
		const Package& package = wspc.GetPackage(i);
		int packageNode = -1;
		for (const auto& file : package.file) {
			String filePath = SourcePath(wspc[i], file);

			if (ToLower(GetFileExt(filePath)) != ".usc")
				continue;
				
			auto list = UscFileParser(filePath).Parse();
			if (list.GetCount() == 0)
				continue;
			
			if(packageNode == -1)
				packageNode = macrosTree.Add(localNode, Image(), LOCAL_MACRO_KEY + 1, wspc[i]);
					
			int fileNode = macrosTree.Add(packageNode, Image(), LOCAL_MACRO_KEY + 2, file);
			for(int j = 0; j < list.GetCount(); j++) {
				MacroElement& element = list[j];
				macrosTree.Add(fileNode, element.GetImage(), RawToValue(element), element.name);
			}
		}
	}
}

void Ide::DoMacroManager()
{
	MacroManagerWindow(*this).Execute();
}
