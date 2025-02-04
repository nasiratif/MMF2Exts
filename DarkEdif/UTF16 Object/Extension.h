#pragma once
class Extension
{
public:
	RUNDATA * rdPtr;
	RunHeader *	rhPtr;

	Edif::Runtime Runtime;

	static const int MinimumBuild = 254;
	static const int Version = 7;

	static const OEFLAGS OEFLAGS = OEFLAGS::NONE;
	static const OEPREFS OEPREFS = OEPREFS::NONE;

	static const int WindowProcPriority = 100;

	Extension(RUNDATA * rdPtr, EDITDATA * edPtr, CreateObjectInfo * cobPtr);
	~Extension();


	/*  Add any data you want to store in your extension to this class
		(eg. what you'd normally store in rdPtr).

		Unlike rdPtr, you can store real C++ objects with constructors
		and destructors, without having to call them manually or store
		a pointer.
	*/




	// int MyVariable;




	/*  Add your actions, conditions and expressions as real class member
		functions here. The arguments (and return type for expressions) must
		match EXACTLY what you defined in the JSON.

		Remember to link the actions, conditions and expressions to their
		numeric IDs in the class constructor (Extension.cpp)
	*/

		bool IsBadMemoryAddress(const void * const address);

	/// Actions
		void UTF16StrToUTF16Mem(const wchar_t * utf16Str, int addr, int excludeNull);

	/// Conditions

	/// Expressions

		int UTF16CharToUTF16Int(const wchar_t * utf16Char);
		const wchar_t * UTF16IntToUTF16Char(unsigned int utf16ints);
		const wchar_t * UTF16StrFromUTF16Mem(int addr, int numChars);
		const wchar_t * UTF16StrFromUTF8Mem(int addr, int numChars);



	/* These are called if there's no function linked to an ID */

	void UnlinkedAction(int ID);
	long UnlinkedCondition(int ID);
	long UnlinkedExpression(int ID);




	/*  These replace the functions like HandleRunObject that used to be
		implemented in Runtime.cpp. They work exactly the same, but they're
		inside the extension class.
	*/

	REFLAG Handle();
	REFLAG Display();

	short FusionRuntimePaused();
	short FusionRuntimeContinued();

	bool SaveFramePosition(HANDLE File);
	bool LoadFramePosition(HANDLE File);

};
