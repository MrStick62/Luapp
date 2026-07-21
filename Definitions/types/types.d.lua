------------------
-- Config class --
------------------

export type ConfigData = { [string | number]: ConfigData | number | string | boolean }

declare class Config_Class
    --- Saves config data as a json to the specified file path. Path is always relative to the main file
    Save: (Config: ConfigData, Path: string) -> ()
    --- Loads config data from a json file at the specified path. Path is always relative to the main file
    Load: (Path: string) -> ConfigData
end

declare Config: Config_Class

----------------
-- Vec2 class --
----------------

export type Vec2Data = {
    X: number,
    Y: number,
}

declare class Vec2
    X: number
    Y: number

    function __add(self, Value: Vec2): Vec2
    function __sub(self, Value: Vec2): Vec2
    function __mul(self, Value: number): Vec2
    function __div(self, Value: number): Vec2
end

declare class Vec2_Class
    New: (X: number, Y: number) -> Vec2
    Lerp: (V1: Vec2, V2: Vec2, T: number) -> Vec2
end

declare Vec2: Vec2_Class

-----------------
-- Color class --
-----------------

export type Color = {
    R: number,
    G: number,
    B: number,
    A: number,
}

declare class Color_Class
    New: (R: number, G: number, B: number, A: number) -> Color
end

declare Color: Color_Class

-----------------
-- Flags class --
-----------------

declare class Flags
end

declare class Flags_Class
	Unite: (Flags: { Flags }) -> Flags
end

declare Flags: Flags_Class

-----------------
-- Image class --
-----------------

declare class Image
    function Destroy(self): ()
    function GetSize(self): Vec2
end

declare class Image_Class
    New: (FilePath: string) -> Image
end

declare Image: Image_Class

----------------
-- Font class --
----------------

declare class Font
    Name: string
end

declare class Font_Class
    --- Load a font from a .ttf file. Path is always relative to the main file
    --- Automatically added to the font list returned from GetAll()
    LoadNew: (FontPath: string, IconPath: string?) -> Font
    --- Returns a list of all loaded fonts
    GetAll: () -> { Font }
end

declare Font: Font_Class

-----------------------
-- Gui color indices --
-----------------------

type GuiColor = number

declare class GuiColors
end

declare class GuiColors_Class
    Text: GuiColor
    TextDisabled: GuiColor
    WindowBg: GuiColor
    ChildBg: GuiColor
    PopupBg: GuiColor
    Border: GuiColor
    BorderShadow: GuiColor
    FrameBg: GuiColor
    FrameBgHovered: GuiColor
    FrameBgActive: GuiColor
    TitleBg: GuiColor
    TitleBgActive: GuiColor
    TitleBgCollapsed: GuiColor
    MenuBarBg: GuiColor
    ScrollbarBg: GuiColor
    ScrollbarGrab: GuiColor
    ScrollbarGrabHovered: GuiColor
    ScrollbarGrabActive: GuiColor
    CheckMark: GuiColor
    SliderGrab: GuiColor
    SliderGrabActive: GuiColor
    Button: GuiColor
    ButtonHovered: GuiColor
    ButtonActive: GuiColor
    Header: GuiColor
    HeaderHovered: GuiColor
    HeaderActive: GuiColor
    Separator: GuiColor
    SeparatorHovered: GuiColor
    SeparatorActive: GuiColor
    ResizeGrip: GuiColor
    ResizeGripHovered: GuiColor
    ResizeGripActive: GuiColor
    InputTextCursor: GuiColor
    TabHovered: GuiColor
    Tab: GuiColor
    TabSelected: GuiColor
    TabSelectedOverline: GuiColor
    TabDimmed: GuiColor
    TabDimmedSelected: GuiColor
    TabDimmedSelectedOverline: GuiColor
    PlotLines: GuiColor
    PlotLinesHovered: GuiColor
    PlotHistogram: GuiColor
    PlotHistogramHovered: GuiColor
    TableHeaderBg: GuiColor
    TableBorderStrong: GuiColor
    TableBorderLight: GuiColor
    TableRowBg: GuiColor
    TableRowBgAlt: GuiColor
    TextLink: GuiColor
    TextSelectedBg: GuiColor
    TreeLines: GuiColor
    DragDropTarget: GuiColor
    DragDropTargetBg: GuiColor
    UnsavedMarker: GuiColor
    NavCursor: GuiColor
    NavWindowingHighlight: GuiColor
    NavWindowingDimBg: GuiColor
    ModalWindowDimBg: GuiColor
end

declare GuiColors: GuiColors_Class

---------------------------
-- Gui style var indices --
---------------------------

type GuiStyleVar = number

declare class GuiStyleVars_Class
    Alpha: GuiStyleVar                    -- number 
    DisabledAlpha: GuiStyleVar            -- number
    WindowPadding: GuiStyleVar            -- Vec2 
    WindowRounding: GuiStyleVar           -- number
    WindowBorderSize: GuiStyleVar         -- number
    WindowMinSize: GuiStyleVar            -- Vec2
    WindowTitleAlign: GuiStyleVar         -- Vec2
    ChildRounding: GuiStyleVar            -- number
    ChildBorderSize: GuiStyleVar          -- number
    PopupRounding: GuiStyleVar            -- number
    PopupBorderSize: GuiStyleVar          -- number
    FramePadding: GuiStyleVar             -- Vec2
    FrameRounding: GuiStyleVar            -- number
    FrameBorderSize: GuiStyleVar          -- number
    ItemSpacing: GuiStyleVar              -- Vec2
    ItemInnerSpacing: GuiStyleVar         -- Vec2
    IndentSpacing: GuiStyleVar            -- number
    CellPadding: GuiStyleVar              -- Vec2
    ScrollbarSize: GuiStyleVar            -- number
    ScrollbarRounding: GuiStyleVar        -- number
    ScrollbarPadding: GuiStyleVar         -- number
    GrabMinSize: GuiStyleVar              -- number
    GrabRounding: GuiStyleVar             -- number
    ImageRounding: GuiStyleVar            -- number
    ImageBorderSize: GuiStyleVar          -- number
    TabRounding: GuiStyleVar              -- number
    TabBorderSize: GuiStyleVar            -- number
    TabMinWidthBase: GuiStyleVar          -- number
    TabMinWidthShrink: GuiStyleVar        -- number
    TabBarBorderSize: GuiStyleVar         -- number
    TabBarOverlineSize: GuiStyleVar       -- number
    TableAngledHeadersAngle: GuiStyleVar  -- number
    TableAngledHeadersTextAlign: GuiStyleVar-- Vec2
    TreeLinesSize: GuiStyleVar            -- number
    TreeLinesRounding: GuiStyleVar        -- number
    MenuItemRounding: GuiStyleVar         -- number
    SelectableRounding: GuiStyleVar       -- number
    DragDropTargetRounding: GuiStyleVar   -- number
    ButtonTextAlign: GuiStyleVar          -- Vec2
    SelectableTextAlign: GuiStyleVar      -- Vec2
    SeparatorSize: GuiStyleVar            -- number
    SeparatorTextBorderSize: GuiStyleVar  -- number
    SeparatorTextAlign: GuiStyleVar       -- Vec2
    SeparatorTextPadding: GuiStyleVar     -- Vec2
end

declare GuiStyleVars: GuiStyleVars_Class

---------------------------------
-- Gui table background target --
---------------------------------

declare class GuiTableBgTarget
end

declare class GuiTableBgTarget_Class
	None: GuiTableBgTarget
	RowBg1: GuiTableBgTarget
	RowBg2: GuiTableBgTarget
	CellBg: GuiTableBgTarget
end

declare GuiTableBgTarget: GuiTableBgTarget_Class

-------------------------
-- Gui style structure --
-------------------------

export type GuiStyle = {
	FontSizeBase: number,
    FontScaleDpi: number,
	WindowRounding: number,
	ChildRounding: number,
    FramePadding: Vec2,
	FrameRounding: number,
	ImageRounding: number,
	--- Index with GuiColor
	Colors: { Color },
}

----------------------
-- Gui window flags --
----------------------

export type GuiWindowFlags = Flags

declare class GuiWindowFlags_Class
	None: GuiWindowFlags
	NoTitleBar: GuiWindowFlags
	NoResize: GuiWindowFlags
	NoMove: GuiWindowFlags
	NoScrollBar: GuiWindowFlags
	NoScrollWithMouse: GuiWindowFlags
	NoCollapse: GuiWindowFlags
	AlwaysAutoResize: GuiWindowFlags
	NoBackground: GuiWindowFlags
	NoSavedSettings: GuiWindowFlags
	NoMouseInputs: GuiWindowFlags
	MenuBar: GuiWindowFlags
	HorizontalScrollbar: GuiWindowFlags
	NoFocusOnAppearing: GuiWindowFlags
	NoBringToFrontOnFocus: GuiWindowFlags
	AlwaysVerticalScrollbar: GuiWindowFlags
	AlwaysHorizontalScrollbar: GuiWindowFlags
	NoNavInputs: GuiWindowFlags
	NoNavFocus: GuiWindowFlags
	UnsavedDocument: GuiWindowFlags
	NoDocking: GuiWindowFlags
	NoNav: GuiWindowFlags
	NoDecoration: GuiWindowFlags
	NoInputs: GuiWindowFlags
	DockNodeHost: GuiWindowFlags
	ChildWindow: GuiWindowFlags
	Tooltip: GuiWindowFlags
	Popup: GuiWindowFlags
	Modal: GuiWindowFlags
	ChildMenu: GuiWindowFlags
end

declare GuiWindowFlags: GuiWindowFlags_Class

---------------------
-- Gui child flags --
---------------------

export type GuiChildFlags = Flags

declare class GuiChildFlags_Class
	None: GuiChildFlags
	Borders: GuiChildFlags
	AlwaysUseWindowPadding: GuiChildFlags
	ResizeX: GuiChildFlags
	ResizeY: GuiChildFlags
	AutoResizeX: GuiChildFlags
	AutoResizeY: GuiChildFlags
	AlwaysAutoResize: GuiChildFlags
	FrameStyle: GuiChildFlags
	NavFlattened: GuiChildFlags
end

declare GuiChildFlags: GuiChildFlags_Class

----------------------
-- Gui slider flags --
----------------------

export type GuiButtonFlags = Flags

declare class GuiButtonFlags_Class
	None: GuiButtonFlags
	MouseButtonLeft: GuiButtonFlags
	MouseButtonRight: GuiButtonFlags
	MouseButtonMiddle: GuiButtonFlags
	EnableNav: GuiButtonFlags
	AllowOverlap: GuiButtonFlags
end

declare GuiButtonFlags: GuiButtonFlags_Class

----------------------
-- Gui slider flags --
----------------------

export type GuiSliderFlags = Flags

declare class GuiSliderFlags_Class
	None: GuiSliderFlags
	Logarithmic: GuiSliderFlags
	NoRoundToFormat: GuiSliderFlags
	NoInput: GuiSliderFlags
	WrapAround: GuiSliderFlags
	ClampOnInput: GuiSliderFlags
	ClampZeroRange: GuiSliderFlags
	NoSpeedTweaks: GuiSliderFlags
	ColorMarkers: GuiSliderFlags
	AlwaysClamp: GuiSliderFlags
end

declare GuiSliderFlags: GuiSliderFlags_Class

--------------------------
-- Gui input text flags --
--------------------------

export type GuiInputTextFlags = Flags

declare class GuiInputTextFlags_Class
	None: GuiInputTextFlags
	CharsDecimal: GuiInputTextFlags
	CharsHexadecimal: GuiInputTextFlags
	CharsScientific: GuiInputTextFlags
	CharsUppercase: GuiInputTextFlags
	CharsNoBlank: GuiInputTextFlags
	AllowTabInput: GuiInputTextFlags
	EnterReturnsTrue: GuiInputTextFlags
	EscapeClearsAll: GuiInputTextFlags
	CtrlEnterForNewLine: GuiInputTextFlags
	ReadOnly: GuiInputTextFlags
	Password: GuiInputTextFlags
	AlwaysOverwrite: GuiInputTextFlags
	AutoSelectAll: GuiInputTextFlags
	ParseEmptyRefVal: GuiInputTextFlags
	DisplayEmptyRefVal: GuiInputTextFlags
	NoHorizontalScroll: GuiInputTextFlags
	NoUndoRedo: GuiInputTextFlags
	ElideLeft: GuiInputTextFlags
	CallbackCompletion: GuiInputTextFlags
	CallbackHistory: GuiInputTextFlags
	CallbackAlways: GuiInputTextFlags
	CallbackCharFilter: GuiInputTextFlags
	CallbackResize: GuiInputTextFlags
	CallbackEdit: GuiInputTextFlags
	WordWrap: GuiInputTextFlags
end

declare GuiInputTextFlags: GuiInputTextFlags_Class

-------------------------
-- Gui tree node flags --
-------------------------

export type GuiTreeNodeFlags = Flags

declare class GuiTreeNodeFlags_Class
	None: GuiTreeNodeFlags
	Selected: GuiTreeNodeFlags
	Framed: GuiTreeNodeFlags
	AllowOverlap: GuiTreeNodeFlags
	NoTreePushOnOpen: GuiTreeNodeFlags
	NoAutoOpenOnLog: GuiTreeNodeFlags
	DefaultOpen: GuiTreeNodeFlags
	OpenOnDoubleClick: GuiTreeNodeFlags
	OpenOnArrow: GuiTreeNodeFlags
	Leaf: GuiTreeNodeFlags
	Bullet: GuiTreeNodeFlags
	FramePadding: GuiTreeNodeFlags
	SpanAvailWidth: GuiTreeNodeFlags
	SpanFullWidth: GuiTreeNodeFlags
	SpanLabelWidth: GuiTreeNodeFlags
	SpanAllColumns: GuiTreeNodeFlags
	LabelSpanAllColumns: GuiTreeNodeFlags
	NavLeftJumpsToParent: GuiTreeNodeFlags
	CollapsingHeader: GuiTreeNodeFlags
	DrawLinesNone: GuiTreeNodeFlags
	DrawLinesFull: GuiTreeNodeFlags
	DrawLinesToNodes: GuiTreeNodeFlags
end

declare GuiTreeNodeFlags: GuiTreeNodeFlags_Class

--------------------------
-- Gui selectable flags --
--------------------------

export type GuiSelectableFlags = Flags

declare class GuiSelectableFlags_Class
	None: GuiSelectableFlags
	NoAutoClosePopups: GuiSelectableFlags
	SpanAllColumns: GuiSelectableFlags
	AllowDoubleClick: GuiSelectableFlags
	Disabled: GuiSelectableFlags
	AllowOverlap: GuiSelectableFlags
	Highlight: GuiSelectableFlags
	SelectOnNav: GuiSelectableFlags
end

declare GuiSelectableFlags: GuiSelectableFlags_Class

-----------------------
-- Gui tab bar flags --
-----------------------

export type GuiTabBarFlags = Flags

declare class GuiTabBarFlags_Class
	None: GuiTabBarFlags
	Reorderable: GuiTabBarFlags
	AutoSelectNewTabs: GuiTabBarFlags
	TabListPopupButton: GuiTabBarFlags
	NoCloseWithMiddleMouseButton: GuiTabBarFlags
	NoTabListScrollingButtons: GuiTabBarFlags
	NoTooltip: GuiTabBarFlags
	DrawSelectedOverline: GuiTabBarFlags
	FittingPolicyMixed: GuiTabBarFlags
	FittingPolicyShrink: GuiTabBarFlags
	FittingPolicyScroll: GuiTabBarFlags
end

declare GuiTabBarFlags: GuiTabBarFlags_Class

------------------------
-- Gui tab item flags --
------------------------

export type GuiTabItemFlags = Flags

declare class GuiTabItemFlags_Class
	None: GuiTabItemFlags
	UnsavedDocument: GuiTabItemFlags
	SetSelected: GuiTabItemFlags
	NoCloseWithMiddleMouseButton: GuiTabItemFlags
	NoPushId: GuiTabItemFlags
	NoTooltip: GuiTabItemFlags
	NoReorder: GuiTabItemFlags
	Leading: GuiTabItemFlags
	Trailing: GuiTabItemFlags
	NoAssumedClosure: GuiTabItemFlags
end

declare GuiTabItemFlags: GuiTabItemFlags_Class

---------------------
-- Gui table flags --
---------------------

export type GuiTableFlags = Flags

declare class GuiTableFlags_Class
	None: GuiTableFlags
	Resizable: GuiTableFlags
	Reorderable: GuiTableFlags
	Hideable: GuiTableFlags
	Sortable: GuiTableFlags
	NoSavedSettings: GuiTableFlags
	ContextMenuInBody: GuiTableFlags
	RowBg: GuiTableFlags
	BordersInnerH: GuiTableFlags
	BordersOuterH: GuiTableFlags
	BordersInnerV: GuiTableFlags
	BordersOuterV: GuiTableFlags
	BordersH: GuiTableFlags
	BordersV: GuiTableFlags
	BordersInner: GuiTableFlags
	BordersOuter: GuiTableFlags
	Borders: GuiTableFlags
	NoBordersInBody: GuiTableFlags
	NoBordersInBodyUntilResize: GuiTableFlags
	SizingFixedFit: GuiTableFlags
	SizingFixedSame: GuiTableFlags
	SizingStretchProp: GuiTableFlags
	SizingStretchSame: GuiTableFlags
	NoHostExtendX: GuiTableFlags
	NoHostExtendY: GuiTableFlags
	NoKeepColumnsVisible: GuiTableFlags
	PreciseWidths: GuiTableFlags
	NoClip: GuiTableFlags
	PadOuterX: GuiTableFlags
	NoPadOuterX: GuiTableFlags
	NoPadInnerX: GuiTableFlags
	ScrollX: GuiTableFlags
	ScrollY: GuiTableFlags
	SortMulti: GuiTableFlags
	SortTristate: GuiTableFlags
	HighlightHoveredColumn: GuiTableFlags
end

declare GuiTableFlags: GuiTableFlags_Class

----------------------------
-- Gui table column flags --
----------------------------

export type GuiTableColumnFlags = Flags

declare class GuiTableColumnFlags_Class
	None: GuiTableColumnFlags
	Disabled: GuiTableColumnFlags
	DefaultHide: GuiTableColumnFlags
	DefaultSort: GuiTableColumnFlags
	WidthStretch: GuiTableColumnFlags
	WidthFixed: GuiTableColumnFlags
	NoResize: GuiTableColumnFlags
	NoReorder: GuiTableColumnFlags
	NoHide: GuiTableColumnFlags
	NoClip: GuiTableColumnFlags
	NoSort: GuiTableColumnFlags
	NoSortAscending: GuiTableColumnFlags
	NoSortDescending: GuiTableColumnFlags
	NoHeaderLabel: GuiTableColumnFlags
	NoHeaderWidth: GuiTableColumnFlags
	PreferSortAscending: GuiTableColumnFlags
	PreferSortDescending: GuiTableColumnFlags
	IndentEnable: GuiTableColumnFlags
	IndentDisable: GuiTableColumnFlags
	AngledHeader: GuiTableColumnFlags
	IsEnabled: GuiTableColumnFlags
	IsVisible: GuiTableColumnFlags
	IsSorted: GuiTableColumnFlags
	IsHovered: GuiTableColumnFlags
end

declare GuiTableColumnFlags: GuiTableColumnFlags_Class

-------------------------
-- Gui table row flags --
-------------------------

export type GuiTableRowFlags = Flags

declare class GuiTableRowFlags_Class
	None: GuiTableRowFlags
	Headers: GuiTableRowFlags
end

declare GuiTableRowFlags: GuiTableRowFlags_Class

--------------------
-- Main Gui class --
--------------------

-- The Gui class is essentially a Luau wrapper for the C++ Gui library Dear ImGui
-- To take advantage of Luau's unique features, some functions have slightly different behaviors from ImGui
-- Visit https://github.com/ocornut/imgui for more detailed documentation on the library

-- Bonus tips:
-- 1. Hide the label of a Gui item by prefixing the string with "##"

declare class Gui_Class
    --- Saves the Gui layout in a file at the specified path. Path is always relative to the main file
    SetSaveFile: (Path: string) -> ()

    --- Call before Begin() to specify the size of the window
	SetNextWindowSize: (Size: Vec2) -> ()
    --- Call before Begin() to specify the position of the window
	SetNextWindowPos: (Size: Vec2) -> ()
    --- Call before Begin() to specify the minimum and maximum size of the next window
	SetNextWindowSizeConstraints: (Min: Vec2, Max: Vec2) -> ()

    --- These horrible functions killed my family back in 2005
    --- You probably want to use GetContentRegionAvail() and GetCursorScreenPos() instead
	GetWindowSize: () -> Vec2
	GetWindowPos: () -> Vec2

    --- The cursor represents the position of the next output gui output
    --- CursorScreenPos is the "absolute" coordinate, while CursorPos is relative to the current window
	GetCursorScreenPos: () -> Vec2
	SetCursorScreenPos: (Pos: Vec2) -> ()

	GetCursorPos: () -> Vec2
	SetCursorPos: (Pos: Vec2) -> ()

    --- Returns the available space remaining in the window from the current cursor position
	--- This beautiful function saved my life back in 2005
	GetContentRegionAvail: () -> Vec2 

	--- Begins rendering a new window. Must be followed by an End() call after content is specified
	--- First return return value true if the content should be rendered, false if it is collapsed
	--- Second is whether it should stay open (only applies if IsOpen is passed)
	Begin: (Name: string, IsOpen: boolean?, Flags: GuiWindowFlags?) -> (boolean, boolean)
	End: () -> ()

    --- Creates a self-contained child window within the window currently being rendered
    --- Must be followed by EndChild() after rendering content has been specified
	BeginChild: (ID: string, Size: Vec2, ChildFlags: GuiChildFlags?, WindowFlags: GuiWindowFlags?) -> boolean
	EndChild: () -> ()

    --- Creates a menu bar at the top of the application
    --- Must be followed by EndMainMenuBar() if it returns true
	BeginMainMenuBar: () -> boolean
	EndMainMenuBar: () -> ()
	
    --- Creates a menu bar at the top of the window currently being rendered
    --- Must be followed by EndMenuBar() if it returns true
	--- MenuBar window flag must be present in the parent window for this to work
	BeginMenuBar: () -> boolean
	EndMenuBar: () -> ()

    --- Creates a menu entry on the current menu bar
    --- Must be followed by EndMenu() if it returns true
	BeginMenu: (Label: string, Enabled: boolean?) -> boolean
	EndMenu: () -> ()

    --- Creates a selectable element within a menu
    --- Returns true when clicked
	MenuItem: (Label: string, Shortcut: string?, Selected: boolean?, Enabled: boolean?) -> boolean

	BeginTabBar: (ID: string, Flags: GuiTabBarFlags?) -> boolean
	EndTabBar: () -> ()

	BeginTabItem: (Label: string, IsOpen: boolean?, Flags: GuiTabItemFlags?) -> (boolean, boolean)
	EndTabItem: () -> ()

	BeginPopup: (ID: string, Flags: GuiWindowFlags) -> boolean
	EndPopup: () -> ()

	BeginTable: (ID: string, Columns: number, Flags: GuiTableFlags?, OuterSize: Vec2?, InnerWidth: number?) -> boolean
	EndTable: () -> ()

	TableNextRow: (Flags: GuiTableRowFlags?, MinRowHeight: number?) -> ()
	TableNextColumn: () -> boolean
	TableSetColumnIndex: (Index: number) -> boolean

	TableSetupColumn: (Label: string, Flags: GuiTableColumnFlags?, InitWidth: number?) -> ()
	TableSetupScrollFreeze: (Columns: number, Rows: number) -> ()
	TableHeader: (Label: string) -> ()
	TableHeadersRow: () -> ()
	TableAngledHeadersRow: () -> ()

	TableSetBgColor: (Target: GuiTableBgTarget, Color: Color, Column: number?) -> ()

    --- Grays out colors and disables interactions with the following content
    --- Must be followed by EndDisabled() after content is specified
	BeginDisabled: () -> ()
	EndDisabled: () -> ()

    --- Because a Gui item's label acts as its ID, you cannot create multiple items with the same label within a window
    --- To get around this, PushID/PopID provides a means of resetting the ID scope with a unique ID
    --- This is primarily used to create repeat items within a loop without getting errors
    --- PushID() must be followed by PopID() before the end of the current window
	PushID: (ID: string) -> ()
	PushID: (ID: number) -> () -- Must be a whole number
	PopID: () -> ()

	SameLine: (Offset: number?, Spacing: number?) -> ()
	Spacing: (Spaces: number?) -> ()
	Indent: (Width: number?) -> ()
	Unindent: (Width: number?) -> ()
	Separator: () -> ()
	Bullet: () -> ()

	CollapsingHeader: (Label: string, Flags: GuiTreeNodeFlags?) -> boolean

	Image: (Image: Image, Size: Vec2?, UV1: Vec2?, UV2: Vec2?) -> ()
	ImageWithBg: (Image: Image, Size: Vec2?, UV1: Vec2?, UV2: Vec2?, Background: Color?, Tint: Color?) -> boolean
	ImageButton: (ID: string, Image: Image, Size: Vec2?, UV1: Vec2?, UV2: Vec2?, Background: Color?, Tint: Color?) -> boolean

    --- Creates a line of formatted text in the current window
    --- If no color is specified, uses the default text color of the current style/theme
    --- Wrapped text automatically jumps to the next line to fit itself in the available space of the window
    Text: (Text: string, Color: Color?, Wrapped: boolean?) -> ()
    --- Formatted ext with a Separator() line through it
	SeparatorText: (Text: string) -> ()
    --- Text that returns true when clicked
	TextLink: (Text: string) -> boolean
    --- Essentially a hyperlink. Opens the specified URL when clicked
	TextLinkOpenURL: (Label: string, URL: string) -> boolean

    --- Returns the size of a formatted line of text if you were to draw it
	CalcTextSize: (Text: string) -> Vec2

    --- Creates a text box for editing string values
    --- The first value returned is the edited input string
    --- The second value is true if edited this frame
	InputText: (Label: string, Input: string, Flags: GuiInputTextFlags?) -> (string, boolean)
    InputTextWithHint: (Label: string, Hint: string, Input: string, Flags: GuiInputTextFlags?) -> (string, boolean)
	InputTextMultiline: (Label: string, Input: string, Size: Vec2?, Flags: GuiInputTextFlags?) -> (string, boolean)
    --- Input text for editing numbers
	InputFloat: (Label: string, Value: number, Precision: number?, Flags: GuiInputTextFlags?) -> (number, boolean)
    --- Input text for editing whole numbers
	InputInt: (Label: string, Value: number, Flags: GuiInputTextFlags?) -> (number, boolean)

	Button: (Label: string, Size: Vec2?) -> boolean
	SmallButton: (Label: string) -> boolean
	InvisibleButton: (ID: string, Size: Vec2, Flags: GuiButtonFlags?) -> boolean
	Checkbox: (Label: string, Checked: boolean) -> boolean

    IsItemHovered: () -> boolean

	Selectable: (Label: string, Selected: boolean, Flags: GuiSelectableFlags?, Size: Vec2?) -> boolean

	--- Creates a drop down list of selectable items
	--- First return value is the new index of the currently selected item
	--- Second returns true when the selected item is changed
	Combo: (Label: string, CurrentItem: number, Items: { string }, MaxPopupSize: number?) -> (number, boolean)

	SliderFloat: (Label: string, Value: number, Min: number, Max: number, Precision: number?, Flags: GuiSliderFlags?) -> number
	ColorEdit: (Label: string, Color: Color) -> Color

	PlotLines: (Label: string, Values: { number }, OverlayText: string?, Size: Vec2?) -> ()

	GetCurrentFont: () -> Font
	SetFont: (Font: Font) -> ()

	PushFont: (Font: Font?, Size: number?) -> ()
	PopFont: () -> ()

	GetCurrentStyle: () -> GuiStyle
	GetDarkStyle: () -> GuiStyle
	GetLightStyle: () -> GuiStyle
	GetClassicStyle: () -> GuiStyle
	--- Applies the specified theme. Should only be called between frames (from Tick)
	SetStyle: (Style: GuiStyle) -> ()

	PushStyleColor: (Index: GuiColor, Color: Color) -> ()
	PopStyleColor: (Count: number?) -> ()
	GetStyleColorName: (Index: GuiColor) -> string

	PushStyleVar: (Index: GuiStyleVar, Value: number) -> ()
	PushStyleVar: (Index: GuiStyleVar, Value: Vec2) -> ()
	PopStyleVar: (Count: number?) -> ()

	ShowDemoWindow: (IsOpen: boolean?) -> ()
	ShowIDStackToolWindow: (IsOpen: boolean?) -> ()
	ShowFontSelector: (Label: string) -> ()
end

declare Gui: Gui_Class

------------------
-- Window class --
------------------

declare class Window_Class
    GetSize: () -> Vec2
    SetSize: (Size: Vec2) -> ()
    SetSizeLimits: (Min: Vec2?, Max: Vec2?) -> ()

    SetTitle: (Title: string) -> ()

    Close: () -> ()
end

declare Window: Window_Class

---------------
-- Web class --
---------------

declare class Web_Class
    OpenPage: (URL: string) -> boolean
    ConnectToSystem: (Hostname: string, ScreenWidth: number?, ScreenHeight: number?, Username: string?) -> ()
end

declare Web: Web_Class

---------------------
-- Input keys enum --
---------------------

declare class InputKey
end

declare class InputKey_Class
    None: InputKey
    Tab: InputKey
    LeftArrow: InputKey
    RightArrow: InputKey
    UpArrow: InputKey
    DownArrow: InputKey
    PageUp: InputKey
    PageDown: InputKey
    Home: InputKey
    End: InputKey
    Insert: InputKey
    Delete: InputKey
    Backspace: InputKey
    Space: InputKey
    Enter: InputKey
    Escape: InputKey
    LeftCtrl: InputKey 
    LeftShift: InputKey
    LeftAlt: InputKey
    LeftSuper: InputKey
    RightCtrl: InputKey
    RightShift: InputKey
    RightAlt: InputKey
    RightSuper: InputKey
    Menu: InputKey
    Num0: InputKey
    Num1: InputKey
    Num2: InputKey
    Num3: InputKey
    Num4: InputKey
    Num5: InputKey
    Num6: InputKey
    Num7: InputKey
    Num8: InputKey
    Num9: InputKey
    A: InputKey
    B: InputKey
    C: InputKey
    D: InputKey
    E: InputKey
    F: InputKey
    G: InputKey
    H: InputKey
    I: InputKey
    J: InputKey
    K: InputKey
    L: InputKey
    M: InputKey
    N: InputKey
    O: InputKey
    P: InputKey
    Q: InputKey
    R: InputKey
    S: InputKey
    T: InputKey
    U: InputKey
    V: InputKey
    W: InputKey
    X: InputKey
    Y: InputKey
    Z: InputKey
    F1: InputKey
    F2: InputKey
    F3: InputKey
    F4: InputKey
    F5: InputKey
    F6: InputKey
    F7: InputKey
    F8: InputKey
    F9: InputKey
    F10: InputKey
    F11: InputKey
    F12: InputKey
    F13: InputKey
    F14: InputKey
    F15: InputKey
    F16: InputKey
    F17: InputKey
    F18: InputKey
    F19: InputKey
    F20: InputKey
    F21: InputKey
    F22: InputKey
    F23: InputKey
    F24: InputKey
    Apostrophe: InputKey
    Comma: InputKey
    Minus: InputKey
    Period: InputKey
    Slash: InputKey
    Semicolon: InputKey
    Equal: InputKey
    LeftBracket: InputKey
    Backslash: InputKey
    RightBracket: InputKey
    GraveAccent: InputKey
    CapsLock: InputKey
    ScrollLock: InputKey
    NumLock: InputKey
    PrintScreen: InputKey
    Pause: InputKey
    Keypad0: InputKey
    Keypad1: InputKey
    Keypad2: InputKey
    Keypad3: InputKey
    Keypad4: InputKey
    Keypad5: InputKey
    Keypad6: InputKey
    Keypad7: InputKey
    Keypad8: InputKey
    Keypad9: InputKey
    KeypadDecimal: InputKey
    KeypadDivide: InputKey
    KeypadMultiply: InputKey
    KeypadSubtract: InputKey
    KeypadAdd: InputKey
    KeypadEnter: InputKey
    KeypadEqual: InputKey
    AppBack: InputKey
    AppForward: InputKey
    Oem102: InputKey
    MouseLeft: InputKey
    MouseRight: InputKey
    MouseMiddle: InputKey
    MouseX1: InputKey
    MouseX2: InputKey
    MouseWheelX: InputKey
    MouseWheelY: InputKey
    ReservedForModCtrl: InputKey
    ReservedForModShift: InputKey
    ReservedForModAlt: InputKey
    ReservedForModSuper: InputKey
end

declare InputKey: InputKey_Class

export type InputMod = Flags

declare class InputMod_Class
    Ctrl: InputMod -- Ctrl (non-MacOS), Cmd (MacOS)
    Shift: InputMod
    Alt: InputMod
    Super: InputMod -- Super (non-MacOs), Ctrl (MacOS)
end

declare InputMod: InputMod_Class

export type InputFlags = Flags

declare class InputFlags_Class
    None: InputFlags
    Repeat: InputFlags
    RouteActive: InputFlags
    RouteFocused: InputFlags
    RouteGlobal: InputFlags
    RouteAlways: InputFlags
    RouteOverFocused: InputFlags
    RouteOverActive: InputFlags
    RouteUnlessBgFocused: InputFlags
    RouteFromRootWindow: InputFlags
    Tooltip: InputFlags
end

declare InputFlags: InputFlags_Class

---------------------
-- Input functions --
---------------------

declare class Input_Class
    --- Returns true if key is being held down
    IsKeyDown: (Key: InputKey) -> boolean
    --- Returns true if key was pressed THIS frame
    IsKeyPressed: (Key: InputKey) -> boolean
    --- Returns true if key was released THIS frame
    IsKeyReleased: (Key: InputKey) -> boolean
    --- Returns true when a combination of Mod(s) + Key are pressed. Only call during the Gui frame (OnGui)
    Shortcut: (Mods: InputMod, Key: InputKey, Flags: InputFlags?) -> boolean
    --- Automatically calls the next ImGui item (Button, MenuItem, etc.) upon triggering the specified shortcut
    SetNextItemShortcut: (Mods: InputMod, Key: InputKey, Flags: InputFlags?) -> ()

    GetClipboardText: () -> string
    SetClipboardText: (Text: string) -> ()
end

declare Input: Input_Class

--------------------
-- Icon list enum --
--------------------

declare class Icons_Class
    Num0: string
    Num1: string
    Num2: string
    Num3: string
    Num4: string
    Num5: string
    Num6: string
    Num7: string
    Num8: string
    Num9: string
    A: string
    AddressBook: string
    AddressCard: string
    AlignCenter: string
    AlignJustify: string
    AlignLeft: string
    AlignRight: string
    Anchor: string
    AnchorCircleCheck: string
    AnchorCircleExclamation: string
    AnchorCircleXmark: string
    AnchorLock: string
    AngleDown: string
    AngleLeft: string
    AngleRight: string
    AngleUp: string
    AnglesDown: string
    AnglesLeft: string
    AnglesRight: string
    AnglesUp: string
    Ankh: string
    AppleWhole: string
    Archway: string
    ArrowDown: string
    ArrowDown19: string
    ArrowDown91: string
    ArrowDownAZ: string
    ArrowDownLong: string
    ArrowDownShortWide: string
    ArrowDownUpAcrossLine: string
    ArrowDownUpLock: string
    ArrowDownWideShort: string
    ArrowDownZA: string
    ArrowLeft: string
    ArrowLeftLong: string
    ArrowPointer: string
    ArrowRight: string
    ArrowRightArrowLeft: string
    ArrowRightFromBracket: string
    ArrowRightLong: string
    ArrowRightToBracket: string
    ArrowRightToCity: string
    ArrowRotateLeft: string
    ArrowRotateRight: string
    ArrowTrendDown: string
    ArrowTrendUp: string
    ArrowTurnDown: string
    ArrowTurnUp: string
    ArrowUp: string
    ArrowUp19: string
    ArrowUp91: string
    ArrowUpAZ: string
    ArrowUpFromBracket: string
    ArrowUpFromGroundWater: string
    ArrowUpFromWaterPump: string
    ArrowUpLong: string
    ArrowUpRightDots: string
    ArrowUpRightFromSquare: string
    ArrowUpShortWide: string
    ArrowUpWideShort: string
    ArrowUpZA: string
    ArrowsDownToLine: string
    ArrowsDownToPeople: string
    ArrowsLeftRight: string
    ArrowsLeftRightToLine: string
    ArrowsRotate: string
    ArrowsSpin: string
    ArrowsSplitUpAndLeft: string
    ArrowsToCircle: string
    ArrowsToDot: string
    ArrowsToEye: string
    ArrowsTurnRight: string
    ArrowsTurnToDots: string
    ArrowsUpDown: string
    ArrowsUpDownLeftRight: string
    ArrowsUpToLine: string
    Asterisk: string
    At: string
    Atom: string
    AudioDescription: string
    AustralSign: string
    Award: string
    B: string
    Baby: string
    BabyCarriage: string
    Backward: string
    BackwardFast: string
    BackwardStep: string
    Bacon: string
    Bacteria: string
    Bacterium: string
    BagShopping: string
    Bahai: string
    BahtSign: string
    Ban: string
    BanSmoking: string
    Bandage: string
    BangladeshiTakaSign: string
    Barcode: string
    Bars: string
    BarsProgress: string
    BarsStaggered: string
    Baseball: string
    BaseballBatBall: string
    BasketShopping: string
    Basketball: string
    Bath: string
    BatteryEmpty: string
    BatteryFull: string
    BatteryHalf: string
    BatteryQuarter: string
    BatteryThreeQuarters: string
    Bed: string
    BedPulse: string
    BeerMugEmpty: string
    Bell: string
    BellConcierge: string
    BellSlash: string
    BezierCurve: string
    Bicycle: string
    Binoculars: string
    Biohazard: string
    BitcoinSign: string
    Blender: string
    BlenderPhone: string
    Blog: string
    Bold: string
    Bolt: string
    BoltLightning: string
    Bomb: string
    Bone: string
    Bong: string
    Book: string
    BookAtlas: string
    BookBible: string
    BookBookmark: string
    BookJournalWhills: string
    BookMedical: string
    BookOpen: string
    BookOpenReader: string
    BookQuran: string
    BookSkull: string
    BookTanakh: string
    Bookmark: string
    BorderAll: string
    BorderNone: string
    BorderTopLeft: string
    BoreHole: string
    BottleDroplet: string
    BottleWater: string
    BowlFood: string
    BowlRice: string
    BowlingBall: string
    Box: string
    BoxArchive: string
    BoxOpen: string
    BoxTissue: string
    BoxesPacking: string
    BoxesStacked: string
    Braille: string
    Brain: string
    BrazilianRealSign: string
    BreadSlice: string
    Bridge: string
    BridgeCircleCheck: string
    BridgeCircleExclamation: string
    BridgeCircleXmark: string
    BridgeLock: string
    BridgeWater: string
    Briefcase: string
    BriefcaseMedical: string
    Broom: string
    BroomBall: string
    Brush: string
    Bucket: string
    Bug: string
    BugSlash: string
    Bugs: string
    Building: string
    BuildingCircleArrowRight: string
    BuildingCircleCheck: string
    BuildingCircleExclamation: string
    BuildingCircleXmark: string
    BuildingColumns: string
    BuildingFlag: string
    BuildingLock: string
    BuildingNgo: string
    BuildingShield: string
    BuildingUn: string
    BuildingUser: string
    BuildingWheat: string
    Bullhorn: string
    Bullseye: string
    Burger: string
    Burst: string
    Bus: string
    BusSimple: string
    BusinessTime: string
    C: string
    CableCar: string
    CakeCandles: string
    Calculator: string
    Calendar: string
    CalendarCheck: string
    CalendarDay: string
    CalendarDays: string
    CalendarMinus: string
    CalendarPlus: string
    CalendarWeek: string
    CalendarXmark: string
    Camera: string
    CameraRetro: string
    CameraRotate: string
    Campground: string
    CandyCane: string
    Cannabis: string
    Capsules: string
    Car: string
    CarBattery: string
    CarBurst: string
    CarOn: string
    CarRear: string
    CarSide: string
    CarTunnel: string
    Caravan: string
    CaretDown: string
    CaretLeft: string
    CaretRight: string
    CaretUp: string
    Carrot: string
    CartArrowDown: string
    CartFlatbed: string
    CartFlatbedSuitcase: string
    CartPlus: string
    CartShopping: string
    CashRegister: string
    Cat: string
    CediSign: string
    CentSign: string
    Certificate: string
    Chair: string
    Chalkboard: string
    ChalkboardUser: string
    ChampagneGlasses: string
    ChargingStation: string
    ChartArea: string
    ChartBar: string
    ChartColumn: string
    ChartDiagram: string
    ChartGantt: string
    ChartLine: string
    ChartPie: string
    ChartSimple: string
    Check: string
    CheckDouble: string
    CheckToSlot: string
    Cheese: string
    Chess: string
    ChessBishop: string
    ChessBoard: string
    ChessKing: string
    ChessKnight: string
    ChessPawn: string
    ChessQueen: string
    ChessRook: string
    ChevronDown: string
    ChevronLeft: string
    ChevronRight: string
    ChevronUp: string
    Child: string
    ChildCombatant: string
    ChildDress: string
    ChildReaching: string
    Children: string
    Church: string
    Circle: string
    CircleArrowDown: string
    CircleArrowLeft: string
    CircleArrowRight: string
    CircleArrowUp: string
    CircleCheck: string
    CircleChevronDown: string
    CircleChevronLeft: string
    CircleChevronRight: string
    CircleChevronUp: string
    CircleDollarToSlot: string
    CircleDot: string
    CircleDown: string
    CircleExclamation: string
    CircleH: string
    CircleHalfStroke: string
    CircleInfo: string
    CircleLeft: string
    CircleMinus: string
    CircleNodes: string
    CircleNotch: string
    CirclePause: string
    CirclePlay: string
    CirclePlus: string
    CircleQuestion: string
    CircleRadiation: string
    CircleRight: string
    CircleStop: string
    CircleUp: string
    CircleUser: string
    CircleXmark: string
    City: string
    Clapperboard: string
    Clipboard: string
    ClipboardCheck: string
    ClipboardList: string
    ClipboardQuestion: string
    ClipboardUser: string
    Clock: string
    ClockRotateLeft: string
    Clone: string
    ClosedCaptioning: string
    Cloud: string
    CloudArrowDown: string
    CloudArrowUp: string
    CloudBolt: string
    CloudMeatball: string
    CloudMoon: string
    CloudMoonRain: string
    CloudRain: string
    CloudShowersHeavy: string
    CloudShowersWater: string
    CloudSun: string
    CloudSunRain: string
    Clover: string
    Code: string
    CodeBranch: string
    CodeCommit: string
    CodeCompare: string
    CodeFork: string
    CodeMerge: string
    CodePullRequest: string
    Coins: string
    ColonSign: string
    Comment: string
    CommentDollar: string
    CommentDots: string
    CommentMedical: string
    CommentNodes: string
    CommentSlash: string
    CommentSms: string
    Comments: string
    CommentsDollar: string
    CompactDisc: string
    Compass: string
    CompassDrafting: string
    Compress: string
    Computer: string
    ComputerMouse: string
    Cookie: string
    CookieBite: string
    Copy: string
    Copyright: string
    Couch: string
    Cow: string
    CreditCard: string
    Crop: string
    CropSimple: string
    Cross: string
    Crosshairs: string
    Crow: string
    Crown: string
    Crutch: string
    CruzeiroSign: string
    Cube: string
    Cubes: string
    CubesStacked: string
    D: string
    Database: string
    DeleteLeft: string
    Democrat: string
    Desktop: string
    Dharmachakra: string
    DiagramNext: string
    DiagramPredecessor: string
    DiagramProject: string
    DiagramSuccessor: string
    Diamond: string
    DiamondTurnRight: string
    Dice: string
    DiceD20: string
    DiceD6: string
    DiceFive: string
    DiceFour: string
    DiceOne: string
    DiceSix: string
    DiceThree: string
    DiceTwo: string
    Disease: string
    Display: string
    Divide: string
    Dna: string
    Dog: string
    DollarSign: string
    Dolly: string
    DongSign: string
    DoorClosed: string
    DoorOpen: string
    Dove: string
    DownLeftAndUpRightToCenter: string
    DownLong: string
    Download: string
    Dragon: string
    DrawPolygon: string
    Droplet: string
    DropletSlash: string
    Drum: string
    DrumSteelpan: string
    DrumstickBite: string
    Dumbbell: string
    Dumpster: string
    DumpsterFire: string
    Dungeon: string
    E: string
    EarDeaf: string
    EarListen: string
    EarthAfrica: string
    EarthAmericas: string
    EarthAsia: string
    EarthEurope: string
    EarthOceania: string
    Egg: string
    Eject: string
    Elevator: string
    Ellipsis: string
    EllipsisVertical: string
    Envelope: string
    EnvelopeCircleCheck: string
    EnvelopeOpen: string
    EnvelopeOpenText: string
    EnvelopesBulk: string
    Equals: string
    Eraser: string
    Ethernet: string
    EuroSign: string
    Exclamation: string
    Expand: string
    Explosion: string
    Eye: string
    EyeDropper: string
    EyeLowVision: string
    EyeSlash: string
    F: string
    FaceAngry: string
    FaceDizzy: string
    FaceFlushed: string
    FaceFrown: string
    FaceFrownOpen: string
    FaceGrimace: string
    FaceGrin: string
    FaceGrinBeam: string
    FaceGrinBeamSweat: string
    FaceGrinHearts: string
    FaceGrinSquint: string
    FaceGrinSquintTears: string
    FaceGrinStars: string
    FaceGrinTears: string
    FaceGrinTongue: string
    FaceGrinTongueSquint: string
    FaceGrinTongueWink: string
    FaceGrinWide: string
    FaceGrinWink: string
    FaceKiss: string
    FaceKissBeam: string
    FaceKissWinkHeart: string
    FaceLaugh: string
    FaceLaughBeam: string
    FaceLaughSquint: string
    FaceLaughWink: string
    FaceMeh: string
    FaceMehBlank: string
    FaceRollingEyes: string
    FaceSadCry: string
    FaceSadTear: string
    FaceSmile: string
    FaceSmileBeam: string
    FaceSmileWink: string
    FaceSurprise: string
    FaceTired: string
    Fan: string
    Faucet: string
    FaucetDrip: string
    Fax: string
    Feather: string
    FeatherPointed: string
    Ferry: string
    File: string
    FileArrowDown: string
    FileArrowUp: string
    FileAudio: string
    FileCircleCheck: string
    FileCircleExclamation: string
    FileCircleMinus: string
    FileCirclePlus: string
    FileCircleQuestion: string
    FileCircleXmark: string
    FileCode: string
    FileContract: string
    FileCsv: string
    FileExcel: string
    FileExport: string
    FileFragment: string
    FileHalfDashed: string
    FileImage: string
    FileImport: string
    FileInvoice: string
    FileInvoiceDollar: string
    FileLines: string
    FileMedical: string
    FilePdf: string
    FilePen: string
    FilePowerpoint: string
    FilePrescription: string
    FileShield: string
    FileSignature: string
    FileVideo: string
    FileWaveform: string
    FileWord: string
    FileZipper: string
    Fill: string
    FillDrip: string
    Film: string
    Filter: string
    FilterCircleDollar: string
    FilterCircleXmark: string
    Fingerprint: string
    Fire: string
    FireBurner: string
    FireExtinguisher: string
    FireFlameCurved: string
    FireFlameSimple: string
    Fish: string
    FishFins: string
    Flag: string
    FlagCheckered: string
    FlagUsa: string
    Flask: string
    FlaskVial: string
    FloppyDisk: string
    FlorinSign: string
    Folder: string
    FolderClosed: string
    FolderMinus: string
    FolderOpen: string
    FolderPlus: string
    FolderTree: string
    Font: string
    FontAwesome: string
    Football: string
    Forward: string
    ForwardFast: string
    ForwardStep: string
    FrancSign: string
    Frog: string
    Futbol: string
    G: string
    Gamepad: string
    GasPump: string
    Gauge: string
    GaugeHigh: string
    GaugeSimple: string
    GaugeSimpleHigh: string
    Gavel: string
    Gear: string
    Gears: string
    Gem: string
    Genderless: string
    Ghost: string
    Gift: string
    Gifts: string
    GlassWater: string
    GlassWaterDroplet: string
    Glasses: string
    Globe: string
    GolfBallTee: string
    Gopuram: string
    GraduationCap: string
    GreaterThan: string
    GreaterThanEqual: string
    Grip: string
    GripLines: string
    GripLinesVertical: string
    GripVertical: string
    GroupArrowsRotate: string
    GuaraniSign: string
    Guitar: string
    Gun: string
    H: string
    Hammer: string
    Hamsa: string
    Hand: string
    HandBackFist: string
    HandDots: string
    HandFist: string
    HandHolding: string
    HandHoldingDollar: string
    HandHoldingDroplet: string
    HandHoldingHand: string
    HandHoldingHeart: string
    HandHoldingMedical: string
    HandLizard: string
    HandMiddleFinger: string
    HandPeace: string
    HandPointDown: string
    HandPointLeft: string
    HandPointRight: string
    HandPointUp: string
    HandPointer: string
    HandScissors: string
    HandSparkles: string
    HandSpock: string
    Handcuffs: string
    Hands: string
    HandsAslInterpreting: string
    HandsBound: string
    HandsBubbles: string
    HandsClapping: string
    HandsHolding: string
    HandsHoldingChild: string
    HandsHoldingCircle: string
    HandsPraying: string
    Handshake: string
    HandshakeAngle: string
    HandshakeSimple: string
    HandshakeSimpleSlash: string
    HandshakeSlash: string
    Hanukiah: string
    HardDrive: string
    Hashtag: string
    HatCowboy: string
    HatCowboySide: string
    HatWizard: string
    HeadSideCough: string
    HeadSideCoughSlash: string
    HeadSideMask: string
    HeadSideVirus: string
    Heading: string
    Headphones: string
    HeadphonesSimple: string
    Headset: string
    Heart: string
    HeartCircleBolt: string
    HeartCircleCheck: string
    HeartCircleExclamation: string
    HeartCircleMinus: string
    HeartCirclePlus: string
    HeartCircleXmark: string
    HeartCrack: string
    HeartPulse: string
    Helicopter: string
    HelicopterSymbol: string
    HelmetSafety: string
    HelmetUn: string
    HexagonNodes: string
    HexagonNodesBolt: string
    Highlighter: string
    HillAvalanche: string
    HillRockslide: string
    Hippo: string
    HockeyPuck: string
    HollyBerry: string
    Horse: string
    HorseHead: string
    Hospital: string
    HospitalUser: string
    HotTubPerson: string
    Hotdog: string
    Hotel: string
    Hourglass: string
    HourglassEnd: string
    HourglassHalf: string
    HourglassStart: string
    House: string
    HouseChimney: string
    HouseChimneyCrack: string
    HouseChimneyMedical: string
    HouseChimneyUser: string
    HouseChimneyWindow: string
    HouseCircleCheck: string
    HouseCircleExclamation: string
    HouseCircleXmark: string
    HouseCrack: string
    HouseFire: string
    HouseFlag: string
    HouseFloodWater: string
    HouseFloodWaterCircleArrowRight: string
    HouseLaptop: string
    HouseLock: string
    HouseMedical: string
    HouseMedicalCircleCheck: string
    HouseMedicalCircleExclamation: string
    HouseMedicalCircleXmark: string
    HouseMedicalFlag: string
    HouseSignal: string
    HouseTsunami: string
    HouseUser: string
    HryvniaSign: string
    Hurricane: string
    I: string
    ICursor: string
    IceCream: string
    Icicles: string
    Icons: string
    IdBadge: string
    IdCard: string
    IdCardClip: string
    Igloo: string
    Image: string
    ImagePortrait: string
    Images: string
    Inbox: string
    Indent: string
    IndianRupeeSign: string
    Industry: string
    Infinity: string
    Info: string
    Italic: string
    J: string
    Jar: string
    JarWheat: string
    Jedi: string
    JetFighter: string
    JetFighterUp: string
    Joint: string
    JugDetergent: string
    K: string
    Kaaba: string
    Key: string
    Keyboard: string
    Khanda: string
    KipSign: string
    KitMedical: string
    KitchenSet: string
    KiwiBird: string
    L: string
    LandMineOn: string
    Landmark: string
    LandmarkDome: string
    LandmarkFlag: string
    Language: string
    Laptop: string
    LaptopCode: string
    LaptopFile: string
    LaptopMedical: string
    LariSign: string
    LayerGroup: string
    Leaf: string
    LeftLong: string
    LeftRight: string
    Lemon: string
    LessThan: string
    LessThanEqual: string
    LifeRing: string
    Lightbulb: string
    LinesLeaning: string
    Link: string
    LinkSlash: string
    LiraSign: string
    List: string
    ListCheck: string
    ListOl: string
    ListUl: string
    LitecoinSign: string
    LocationArrow: string
    LocationCrosshairs: string
    LocationDot: string
    LocationPin: string
    LocationPinLock: string
    Lock: string
    LockOpen: string
    Locust: string
    Lungs: string
    LungsVirus: string
    M: string
    Magnet: string
    MagnifyingGlass: string
    MagnifyingGlassArrowRight: string
    MagnifyingGlassChart: string
    MagnifyingGlassDollar: string
    MagnifyingGlassLocation: string
    MagnifyingGlassMinus: string
    MagnifyingGlassPlus: string
    ManatSign: string
    Map: string
    MapLocation: string
    MapLocationDot: string
    MapPin: string
    Marker: string
    Mars: string
    MarsAndVenus: string
    MarsAndVenusBurst: string
    MarsDouble: string
    MarsStroke: string
    MarsStrokeRight: string
    MarsStrokeUp: string
    MartiniGlass: string
    MartiniGlassCitrus: string
    MartiniGlassEmpty: string
    Mask: string
    MaskFace: string
    MaskVentilator: string
    MasksTheater: string
    MattressPillow: string
    Maximize: string
    Medal: string
    Memory: string
    Menorah: string
    Mercury: string
    Message: string
    Meteor: string
    Microchip: string
    Microphone: string
    MicrophoneLines: string
    MicrophoneLinesSlash: string
    MicrophoneSlash: string
    Microscope: string
    MillSign: string
    Minimize: string
    Minus: string
    Mitten: string
    Mobile: string
    MobileButton: string
    MobileRetro: string
    MobileScreen: string
    MobileScreenButton: string
    MoneyBill: string
    MoneyBill1: string
    MoneyBill1Wave: string
    MoneyBillTransfer: string
    MoneyBillTrendUp: string
    MoneyBillWave: string
    MoneyBillWheat: string
    MoneyBills: string
    MoneyCheck: string
    MoneyCheckDollar: string
    Monument: string
    Moon: string
    MortarPestle: string
    Mosque: string
    Mosquito: string
    MosquitoNet: string
    Motorcycle: string
    Mound: string
    Mountain: string
    MountainCity: string
    MountainSun: string
    MugHot: string
    MugSaucer: string
    Music: string
    N: string
    NairaSign: string
    NetworkWired: string
    Neuter: string
    Newspaper: string
    NotEqual: string
    Notdef: string
    NoteSticky: string
    NotesMedical: string
    O: string
    ObjectGroup: string
    ObjectUngroup: string
    OilCan: string
    OilWell: string
    Om: string
    Otter: string
    Outdent: string
    P: string
    Pager: string
    PaintRoller: string
    Paintbrush: string
    Palette: string
    Pallet: string
    Panorama: string
    PaperPlane: string
    Paperclip: string
    ParachuteBox: string
    Paragraph: string
    Passport: string
    Paste: string
    Pause: string
    Paw: string
    Peace: string
    Pen: string
    PenClip: string
    PenFancy: string
    PenNib: string
    PenRuler: string
    PenToSquare: string
    Pencil: string
    PeopleArrows: string
    PeopleCarryBox: string
    PeopleGroup: string
    PeopleLine: string
    PeoplePulling: string
    PeopleRobbery: string
    PeopleRoof: string
    PepperHot: string
    Percent: string
    Person: string
    PersonArrowDownToLine: string
    PersonArrowUpFromLine: string
    PersonBiking: string
    PersonBooth: string
    PersonBreastfeeding: string
    PersonBurst: string
    PersonCane: string
    PersonChalkboard: string
    PersonCircleCheck: string
    PersonCircleExclamation: string
    PersonCircleMinus: string
    PersonCirclePlus: string
    PersonCircleQuestion: string
    PersonCircleXmark: string
    PersonDigging: string
    PersonDotsFromLine: string
    PersonDress: string
    PersonDressBurst: string
    PersonDrowning: string
    PersonFalling: string
    PersonFallingBurst: string
    PersonHalfDress: string
    PersonHarassing: string
    PersonHiking: string
    PersonMilitaryPointing: string
    PersonMilitaryRifle: string
    PersonMilitaryToPerson: string
    PersonPraying: string
    PersonPregnant: string
    PersonRays: string
    PersonRifle: string
    PersonRunning: string
    PersonShelter: string
    PersonSkating: string
    PersonSkiing: string
    PersonSkiingNordic: string
    PersonSnowboarding: string
    PersonSwimming: string
    PersonThroughWindow: string
    PersonWalking: string
    PersonWalkingArrowLoopLeft: string
    PersonWalkingArrowRight: string
    PersonWalkingDashedLineArrowRight: string
    PersonWalkingLuggage: string
    PersonWalkingWithCane: string
    PesetaSign: string
    PesoSign: string
    Phone: string
    PhoneFlip: string
    PhoneSlash: string
    PhoneVolume: string
    PhotoFilm: string
    PiggyBank: string
    Pills: string
    PizzaSlice: string
    PlaceOfWorship: string
    Plane: string
    PlaneArrival: string
    PlaneCircleCheck: string
    PlaneCircleExclamation: string
    PlaneCircleXmark: string
    PlaneDeparture: string
    PlaneLock: string
    PlaneSlash: string
    PlaneUp: string
    PlantWilt: string
    PlateWheat: string
    Play: string
    Plug: string
    PlugCircleBolt: string
    PlugCircleCheck: string
    PlugCircleExclamation: string
    PlugCircleMinus: string
    PlugCirclePlus: string
    PlugCircleXmark: string
    Plus: string
    PlusMinus: string
    Podcast: string
    Poo: string
    PooStorm: string
    Poop: string
    PowerOff: string
    Prescription: string
    PrescriptionBottle: string
    PrescriptionBottleMedical: string
    Print: string
    PumpMedical: string
    PumpSoap: string
    PuzzlePiece: string
    Q: string
    Qrcode: string
    Question: string
    QuoteLeft: string
    QuoteRight: string
    R: string
    Radiation: string
    Radio: string
    Rainbow: string
    RankingStar: string
    Receipt: string
    RecordVinyl: string
    RectangleAd: string
    RectangleList: string
    RectangleXmark: string
    Recycle: string
    Registered: string
    Repeat: string
    Reply: string
    ReplyAll: string
    Republican: string
    Restroom: string
    Retweet: string
    Ribbon: string
    RightFromBracket: string
    RightLeft: string
    RightLong: string
    RightToBracket: string
    Ring: string
    Road: string
    RoadBarrier: string
    RoadBridge: string
    RoadCircleCheck: string
    RoadCircleExclamation: string
    RoadCircleXmark: string
    RoadLock: string
    RoadSpikes: string
    Robot: string
    Rocket: string
    Rotate: string
    RotateLeft: string
    RotateRight: string
    Route: string
    Rss: string
    RubleSign: string
    Rug: string
    Ruler: string
    RulerCombined: string
    RulerHorizontal: string
    RulerVertical: string
    RupeeSign: string
    RupiahSign: string
    S: string
    SackDollar: string
    SackXmark: string
    Sailboat: string
    Satellite: string
    SatelliteDish: string
    ScaleBalanced: string
    ScaleUnbalanced: string
    ScaleUnbalancedFlip: string
    School: string
    SchoolCircleCheck: string
    SchoolCircleExclamation: string
    SchoolCircleXmark: string
    SchoolFlag: string
    SchoolLock: string
    Scissors: string
    Screwdriver: string
    ScrewdriverWrench: string
    Scroll: string
    ScrollTorah: string
    SdCard: string
    Section: string
    Seedling: string
    Server: string
    Shapes: string
    Share: string
    ShareFromSquare: string
    ShareNodes: string
    SheetPlastic: string
    ShekelSign: string
    Shield: string
    ShieldCat: string
    ShieldDog: string
    ShieldHalved: string
    ShieldHeart: string
    ShieldVirus: string
    Ship: string
    Shirt: string
    ShoePrints: string
    Shop: string
    ShopLock: string
    ShopSlash: string
    Shower: string
    Shrimp: string
    Shuffle: string
    ShuttleSpace: string
    SignHanging: string
    Signal: string
    Signature: string
    SignsPost: string
    SimCard: string
    Sink: string
    Sitemap: string
    Skull: string
    SkullCrossbones: string
    Slash: string
    Sleigh: string
    Sliders: string
    Smog: string
    Smoking: string
    Snowflake: string
    Snowman: string
    Snowplow: string
    Soap: string
    Socks: string
    SolarPanel: string
    Sort: string
    SortDown: string
    SortUp: string
    Spa: string
    SpaghettiMonsterFlying: string
    SpellCheck: string
    Spider: string
    Spinner: string
    Splotch: string
    Spoon: string
    SprayCan: string
    SprayCanSparkles: string
    Square: string
    SquareArrowUpRight: string
    SquareBinary: string
    SquareCaretDown: string
    SquareCaretLeft: string
    SquareCaretRight: string
    SquareCaretUp: string
    SquareCheck: string
    SquareEnvelope: string
    SquareFull: string
    SquareH: string
    SquareMinus: string
    SquareNfi: string
    SquareParking: string
    SquarePen: string
    SquarePersonConfined: string
    SquarePhone: string
    SquarePhoneFlip: string
    SquarePlus: string
    SquarePollHorizontal: string
    SquarePollVertical: string
    SquareRootVariable: string
    SquareRss: string
    SquareShareNodes: string
    SquareUpRight: string
    SquareVirus: string
    SquareXmark: string
    StaffSnake: string
    Stairs: string
    Stamp: string
    Stapler: string
    Star: string
    StarAndCrescent: string
    StarHalf: string
    StarHalfStroke: string
    StarOfDavid: string
    StarOfLife: string
    SterlingSign: string
    Stethoscope: string
    Stop: string
    Stopwatch: string
    Stopwatch20: string
    Store: string
    StoreSlash: string
    StreetView: string
    Strikethrough: string
    Stroopwafel: string
    Subscript: string
    Suitcase: string
    SuitcaseMedical: string
    SuitcaseRolling: string
    Sun: string
    SunPlantWilt: string
    Superscript: string
    Swatchbook: string
    Synagogue: string
    Syringe: string
    T: string
    Table: string
    TableCells: string
    TableCellsColumnLock: string
    TableCellsLarge: string
    TableCellsRowLock: string
    TableCellsRowUnlock: string
    TableColumns: string
    TableList: string
    TableTennisPaddleBall: string
    Tablet: string
    TabletButton: string
    TabletScreenButton: string
    Tablets: string
    TachographDigital: string
    Tag: string
    Tags: string
    Tape: string
    Tarp: string
    TarpDroplet: string
    Taxi: string
    Teeth: string
    TeethOpen: string
    TemperatureArrowDown: string
    TemperatureArrowUp: string
    TemperatureEmpty: string
    TemperatureFull: string
    TemperatureHalf: string
    TemperatureHigh: string
    TemperatureLow: string
    TemperatureQuarter: string
    TemperatureThreeQuarters: string
    TengeSign: string
    Tent: string
    TentArrowDownToLine: string
    TentArrowLeftRight: string
    TentArrowTurnLeft: string
    TentArrowsDown: string
    Tents: string
    Terminal: string
    TextHeight: string
    TextSlash: string
    TextWidth: string
    Thermometer: string
    ThumbsDown: string
    ThumbsUp: string
    Thumbtack: string
    ThumbtackSlash: string
    Ticket: string
    TicketSimple: string
    Timeline: string
    ToggleOff: string
    ToggleOn: string
    Toilet: string
    ToiletPaper: string
    ToiletPaperSlash: string
    ToiletPortable: string
    ToiletsPortable: string
    Toolbox: string
    Tooth: string
    ToriiGate: string
    Tornado: string
    TowerBroadcast: string
    TowerCell: string
    TowerObservation: string
    Tractor: string
    Trademark: string
    TrafficLight: string
    Trailer: string
    Train: string
    TrainSubway: string
    TrainTram: string
    Transgender: string
    Trash: string
    TrashArrowUp: string
    TrashCan: string
    TrashCanArrowUp: string
    Tree: string
    TreeCity: string
    TriangleExclamation: string
    Trophy: string
    Trowel: string
    TrowelBricks: string
    Truck: string
    TruckArrowRight: string
    TruckDroplet: string
    TruckFast: string
    TruckField: string
    TruckFieldUn: string
    TruckFront: string
    TruckMedical: string
    TruckMonster: string
    TruckMoving: string
    TruckPickup: string
    TruckPlane: string
    TruckRampBox: string
    Tty: string
    TurkishLiraSign: string
    TurnDown: string
    TurnUp: string
    Tv: string
    U: string
    Umbrella: string
    UmbrellaBeach: string
    Underline: string
    UniversalAccess: string
    Unlock: string
    UnlockKeyhole: string
    UpDown: string
    UpDownLeftRight: string
    UpLong: string
    UpRightAndDownLeftFromCenter: string
    UpRightFromSquare: string
    Upload: string
    User: string
    UserAstronaut: string
    UserCheck: string
    UserClock: string
    UserDoctor: string
    UserGear: string
    UserGraduate: string
    UserGroup: string
    UserInjured: string
    UserLarge: string
    UserLargeSlash: string
    UserLock: string
    UserMinus: string
    UserNinja: string
    UserNurse: string
    UserPen: string
    UserPlus: string
    UserSecret: string
    UserShield: string
    UserSlash: string
    UserTag: string
    UserTie: string
    UserXmark: string
    Users: string
    UsersBetweenLines: string
    UsersGear: string
    UsersLine: string
    UsersRays: string
    UsersRectangle: string
    UsersSlash: string
    UsersViewfinder: string
    Utensils: string
    V: string
    VanShuttle: string
    Vault: string
    VectorSquare: string
    Venus: string
    VenusDouble: string
    VenusMars: string
    Vest: string
    VestPatches: string
    Vial: string
    VialCircleCheck: string
    VialVirus: string
    Vials: string
    Video: string
    VideoSlash: string
    Vihara: string
    Virus: string
    VirusCovid: string
    VirusCovidSlash: string
    VirusSlash: string
    Viruses: string
    Voicemail: string
    Volcano: string
    Volleyball: string
    VolumeHigh: string
    VolumeLow: string
    VolumeOff: string
    VolumeXmark: string
    VrCardboard: string
    W: string
    WalkieTalkie: string
    Wallet: string
    WandMagic: string
    WandMagicSparkles: string
    WandSparkles: string
    Warehouse: string
    Water: string
    WaterLadder: string
    WaveSquare: string
    WebAwesome: string
    WeightHanging: string
    WeightScale: string
    WheatAwn: string
    WheatAwnCircleExclamation: string
    Wheelchair: string
    WheelchairMove: string
    WhiskeyGlass: string
    Wifi: string
    Wind: string
    WindowMaximize: string
    WindowMinimize: string
    WindowRestore: string
    WineBottle: string
    WineGlass: string
    WineGlassEmpty: string
    WonSign: string
    Worm: string
    Wrench: string
    X: string
    XRay: string
    Xmark: string
    XmarksLines: string
    Y: string
    YenSign: string
    YinYang: string
    Z: string
end

declare Icons: Icons_Class