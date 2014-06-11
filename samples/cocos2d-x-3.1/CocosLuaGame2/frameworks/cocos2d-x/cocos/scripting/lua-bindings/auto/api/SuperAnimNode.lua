
--------------------------------
-- @module SuperAnimNode
-- @extend Node

--------------------------------
-- @function [parent=#SuperAnimNode] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #cc.Mat4 mat4
-- @param #bool bool
        
--------------------------------
-- @function [parent=#SuperAnimNode] onDraw 
-- @param self
-- @param #cc.Mat4 mat4
-- @param #bool bool
        
--------------------------------
-- @function [parent=#SuperAnimNode] replaceSprite 
-- @param self
-- @param #string str
-- @param #string str
        
--------------------------------
-- @function [parent=#SuperAnimNode] removeTimeEvent 
-- @param self
-- @param #string str
-- @param #int int
        
--------------------------------
-- @function [parent=#SuperAnimNode] Resume 
-- @param self
        
--------------------------------
-- @function [parent=#SuperAnimNode] registerTimeEvent 
-- @param self
-- @param #string str
-- @param #float float
-- @param #int int
        
--------------------------------
-- @function [parent=#SuperAnimNode] setFlipY 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#SuperAnimNode] setFlipX 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#SuperAnimNode] update 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#SuperAnimNode] GetId 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#SuperAnimNode] GetCurSectionName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#SuperAnimNode] Init 
-- @param self
-- @param #string str
-- @param #int int
-- @param #sa.SuperAnimNodeListener superanimnodelistener
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#SuperAnimNode] Pause 
-- @param self
        
--------------------------------
-- @function [parent=#SuperAnimNode] PlaySection 
-- @param self
-- @param #string str
-- @param #bool bool
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#SuperAnimNode] HasSection 
-- @param self
-- @param #string str
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#SuperAnimNode] IsPause 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#SuperAnimNode] setSpeedFactor 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#SuperAnimNode] IsPlaying 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#SuperAnimNode] GetCurFrame 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#SuperAnimNode] resumeSprite 
-- @param self
-- @param #string str
        
--------------------------------
-- @function [parent=#SuperAnimNode] create 
-- @param self
-- @param #string str
-- @param #int int
-- @param #sa.SuperAnimNodeListener superanimnodelistener
-- @return SuperAnimNode#SuperAnimNode ret (return value: sa.SuperAnimNode)
        
--------------------------------
-- @function [parent=#SuperAnimNode] SuperAnimNode 
-- @param self
        
return nil
