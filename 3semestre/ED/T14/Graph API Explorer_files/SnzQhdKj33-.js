/*!CK:3133405484!*//*1398657839,178146853*/

if (self.CavalryLogger) { CavalryLogger.start_js(["s9VGq"]); }

__d("AdsCFApiSpecFields",[],function(a,b,c,d,e,f){e.exports={ACCOUNT_FIELDS:["id","account_id","age","business_country_code","capabilities","currency","daily_spend_limit","funding_source","funding_source_details","moo_default_conversion_bid","min_daily_budget","name","account_status","timezone_id","timezone_offset_hours_utc","tos_accepted","users","user_role","spend_cap","amount_spent","offsite_pixels_tos_accepted"],USER_PAGE_FIELDS:["id","name","global_brand_page_name","category","link","picture","likes","is_published","is_verified","userpermissions"]};});
__d("AdsUtils",["Assert","underscore.ads"],function(a,b,c,d,e,f,g,h){function i(aa){return aa===Object(aa);}function j(aa,ba){if(Array.isArray(aa)||typeof aa==='string')return aa.indexOf(ba)!==-1;return ba in aa;}function k(aa){if(Array.isArray(aa)||typeof aa==='string')return aa.length;var ba=0;for(var ca in aa)if(Object.prototype.hasOwnProperty.call(aa,ca))ba++;return ba;}function l(aa,ba){var ca=[],da=0;while(aa.length>da){ca.push(aa.slice(da,da+ba));da+=ba;}return ca;}function m(aa,ba){if(aa.length!=ba.length){return false;}else{for(var ca=0;ca<aa.length;ca++){var da=false;for(var ea=0;ea<ba.length;ea++){var fa=true;for(var ga in aa[ca])if(aa[ca][ga]!=ba[ea][ga]){fa=false;break;}if(fa)da=true;}if(!da)return false;}return true;}}function n(aa,ba,ca){var da={};for(var ea=0;ea<aa.length;++ea)da[aa[ea][ba]]=(ca===undefined?aa[ea]:aa[ea][ca]);return da;}function o(aa,ba){var ca={};for(var da=0;da<aa.length;++da){if(ca[aa[da][ba]]===undefined)ca[aa[da][ba]]=[];ca[aa[da][ba]].push(aa[da]);}return ca;}function p(aa){var ba={};for(var ca in aa)ba[aa[ca]]=ca;return ba;}function q(aa,ba){var ca={};for(var da in aa)if(aa.hasOwnProperty(da))ca[da]=aa[da]?aa[da][ba]:undefined;return ca;}function r(aa){var ba=aa;if(aa instanceof Array){ba=aa.map(r);}else if(aa instanceof Object){ba={};for(var ca in aa)if(aa.hasOwnProperty(ca))ba[ca]=r(aa[ca]);}return ba;}function s(aa){return aa.replace(/[A-Z]/g,function(ba){return '_'+ba.toLowerCase();});}function t(aa){return aa.replace(/_[a-z]/g,function(ba){return ba.charAt(1).toUpperCase();});}function u(aa,ba){g.define('scalar',function(ea){return typeof ea==='number'||typeof ea==='boolean';});g.isScalar(ba);var ca={};for(var da=0;da<aa.length;++da)ca[aa[da]]=ba;return ca;}function v(aa,ba,ca){var da={},ea=h.union(Object.keys(aa),Object.keys(ba));for(var fa=0;fa<ea.length;fa++){var ga=ea[fa],ha=ca(aa.hasOwnProperty(ga),ba.hasOwnProperty(ga));if(ha<0){da[ga]=aa[ga];}else if(ha>0)da[ga]=ba[ga];}return da;}function w(aa,ba){return v(aa,ba,function(ca,da){return ca&&da?-1:0;});}function x(aa,ba){return v(aa,ba,function(ca,da){return ca?-1:1;});}var y=function(aa,ba,ca,da){da=da||(function(ga,ha){return ga==ha;});if(aa.length===0)return ca;var ea=ba(aa[0]),fa=!aa.some(function(ga){return !da(ba(ga),ea);});if(fa){return ea;}else return ca;};function z(aa,ba){if(Array.isArray(aa)&&Array.isArray(ba)){if(aa.length!==ba.length)return false;for(var ca=0;ca<aa.length;++ca)if(!z(aa[ca],ba[ca]))return false;return true;}else if(i(aa)&&i(ba)){for(var da in aa){if(!aa.hasOwnProperty(da))continue;if(!ba.hasOwnProperty(da))return false;if(!z(aa[da],ba[da]))return false;}return true;}return aa==ba;}e.exports={isObject:i,contains:j,count:k,chunkArray:l,arraysOfMapEquals:m,indexedMap:n,invertedMap:o,flip:p,pluckPreserveKey:q,clone:r,underscoreKey:s,camelCaseKey:t,mapIntersectKey:w,mapUnionKey:x,mapFill:u,getSharedValue:y,isEqualWeak:z};});
__d("adsGKCheck",["AdsCreationConfig","invariant"],function(a,b,c,d,e,f,g){function h(j){return !!g.gk[j];}function i(j,k){g.gk[j]=k;}h.overrideGK=i;e.exports=h;});
__d("AbstractPopoverButton.react",["ReactPropTypes","React","URI","cloneWithProps","cx","joinClasses","merge"],function(a,b,c,d,e,f,g,h,i,j,k,l,m){var n=h.createClass({displayName:'AbstractPopoverButton',propTypes:{config:g.object.isRequired,haschevron:g.bool,maxwidth:g.number},getDefaultProps:function(){return {haschevron:true};},render:function(){var o=this.props.config,p=o.button.componentClass(m(o.button.props),null);p.props.image=null;var q=null;if(this.props.image)q=j(this.props.image,{className:'mrs'});if(q||this.props.label)p.props.label=h.DOM.span({className:"_55pe"},q,this.props.label);if(this.props.haschevron)p.props.imageRight=o.chevron;p.props.className=l(p.props.className,"_2agf");p.props.href=i('#');var r=o.defaultMaxWidth;if(typeof this.props.maxwidth!=='undefined')r=this.props.maxwidth;if(r){var s=this.props.haschevron?r-o.chevronWidth:r;if(this.props.label)p.props.label.props.style={maxWidth:s+'px'};p.props.style=m(p.props.style,{'max-width':r+'px'});}return this.transferPropsTo(p);}});e.exports=n;});
__d("ReactSelectorUtils",[],function(a,b,c,d,e,f){var g={processAndMutateMenuItems:function(h,i){var j;for(var k=0;k<h.length;k++){var l=h[k].value===i;h[k].selected=l;if(l)j=h[k];}return j;}};e.exports=g;});
__d("AbstractSelector.react",["InlineBlock.react","React","ReactChildren","PopoverMenu.react","ReactPropTypes","ReactSelectorUtils","ContextualLayerAutoFlip","PopoverMenuContextMinWidth","PopoverMenuOverlappingBorder","cloneWithProps","cx","invariant","joinClasses"],function(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s){var t=h.createClass({displayName:'AbstractSelector',propTypes:{config:k.object.isRequired,alignh:k.oneOf(['left','center','right']),name:k.string,overlappingborder:k.bool,onChange:k.func,disabled:k.bool,maxheight:k.number},getInitialState:function(){return {value:(this.props.value!=null?this.props.value:this.props.defaultValue!=null?this.props.defaultValue:this.props.initialValue)};},setMenuValue:function(u){r(this.refs&&this.refs.popover);this._internalChange=true;this.refs.popover.getMenu().setValue(u);this._internalChange=false;},onChange:function(u,v){if(this._internalChange)return;if(this.props.value==null){this.setState({value:v.value});}else this.setMenuValue(this.props.value);if(this.props.onChange)this.props.onChange(v);},componentWillReceiveProps:function(u){if(u.value!=null)this.setState({value:u.value});},render:function(){var u=this.props.config,v=[];i.forEach(this.props.children,function(ca){v.push(ca);});var w=u.menu;w.onChange=this.onChange;w.menuitems=v;w.config.className=s("_575t",w.config.className);w.config.maxheight=this.props.maxheight;var x=l.processAndMutateMenuItems(v,this.state.value),y={label:x.label||x.reactChildren,disabled:this.props.disabled};if(x.icon)y.image=p(x.icon,{});var z=p(u.button,y),aa=[m];if(u.layerBehaviors)aa=aa.concat(u.layerBehaviors);var ba=[n];if(this.props.overlappingborder)ba.push(o);return this.transferPropsTo(g({alignv:"middle",name:null},j({ref:"popover",menu:w,alignh:this.props.alignh,layerBehaviors:aa,behaviors:ba,disabled:this.props.disabled},z),h.DOM.input({type:"hidden",name:this.props.name,value:this.state.value})));},showMenu:function(){r(this.refs&&this.refs.popover);this.refs.popover.showPopover();}});e.exports=t;});
__d("XUIButtonGroup.react",["React","ReactChildren","ReactPropTypes","cx","invariant"],function(a,b,c,d,e,f,g,h,i,j,k){var l=g.createClass({displayName:'XUIButtonGroup',propTypes:{isOverlay:i.bool},render:function(){this.validateButtonSize();var m=(("_51xa")+(this.props.isOverlay?' '+"_51xb":''));return this.transferPropsTo(g.DOM.div({className:m},this.props.children));},validateButtonSize:function(){if(!this.props.isOverlay){var m;h.forEach(this.props.children,function(n){if(n){var o=n.type.getButtonSize(n.props);if(!m){m=o;}else k(o===m);}});}}});e.exports=l;});
__d("XUIPopoverButton.react",["AbstractPopoverButton.react","React","Image.react","XUIButton.react","cx","joinClasses","ix"],function(a,b,c,d,e,f,g,h,i,j,k,l,m){var n=h.createClass({displayName:'ReactXUIPopoverButton',statics:{getButtonSize:function(o){return o.size||'medium';}},render:function(){var o=n.getButtonSize(this.props),p="_55pi";if(this.props.theme==='dark')p=l(p,(("_5vto")+(o==='small'?' '+"_55_o":'')+(o==='medium'?' '+"_55_p":'')+(o==='large'?' '+"_55_q":'')+(o==='xlarge'?' '+"_55_r":'')+(o==='xxlarge'?' '+"_55_s":'')));var q=this.props.chevron;if(!q){var r=this.props.theme==='dark'?m('/images/ui/x/button/dark/chevron.png'):m('/images/ui/x/button/normal/chevron.png');q=i({src:r});}var s={button:{componentClass:j,props:{className:p,image:this.props.image,size:o}},chevron:q,chevronWidth:14,defaultMaxWidth:this.props.maxwidth||200};return this.transferPropsTo(g({config:s}));}});e.exports=n;});
__d("XUISelector.react",["AbstractSelector.react","ContextualLayerPositionClassOnContext","React","XUIPopoverButton.react","ReactXUIMenu","invariant"],function(a,b,c,d,e,f,g,h,i,j,k,l){var m=k.SelectableMenu,n=k.SelectableItem,o=i.createClass({displayName:'ReactXUISelector',statics:{getButtonSize:function(p){return p.size||'medium';}},render:function(){var p={button:j({size:this.props.size,suppressed:this.props.suppressed,theme:"dark",maxwidth:this.props.maxwidth}),menu:m(null),layerBehaviors:[h]};return this.transferPropsTo(g({ref:"abstractSelector",config:p},this.props.children));},showMenu:function(){l(this.refs&&this.refs.abstractSelector);this.refs.abstractSelector.showMenu();}});o.Option=n;e.exports=o;});
__d("dotAccess",[],function(a,b,c,d,e,f){function g(h,i,j){var k=i.split('.');do{var l=k.shift();h=h[l]||j&&(h[l]={});}while(k.length&&h);return h;}e.exports=g;});
__d("mergeDeepInto",["invariant","mergeHelpers"],function(a,b,c,d,e,f,g,h){"use strict";var i=h.ArrayStrategies,j=h.checkArrayStrategy,k=h.checkMergeArrayArgs,l=h.checkMergeLevel,m=h.checkMergeObjectArgs,n=h.isTerminal,o=h.normalizeMergeArg,p=function(t,u,v,w){m(t,u);l(w);var x=u?Object.keys(u):[];for(var y=0;y<x.length;y++){var z=x[y];r(t,u,z,v,w);}},q=function(t,u,v,w){k(t,u);l(w);var x=Math.max(t.length,u.length);for(var y=0;y<x;y++)r(t,u,y,v,w);},r=function(t,u,v,w,x){var y=u[v],z=u.hasOwnProperty(v),aa=z&&n(y),ba=z&&Array.isArray(y),ca=z&&!ba&&!ba,da=t[v],ea=t.hasOwnProperty(v),fa=ea&&n(da),ga=ea&&Array.isArray(da),ha=ea&&!ga&&!ga;if(fa){if(aa){t[v]=y;}else if(ba){t[v]=[];q(t[v],y,w,x+1);}else if(ca){t[v]={};p(t[v],y,w,x+1);}else if(!z)t[v]=da;}else if(ga){if(aa){t[v]=y;}else if(ba){g(i[w]);if(w===i.Clobber)da.length=0;q(da,y,w,x+1);}else if(ca){t[v]={};p(t[v],y,w,x+1);}else !z;}else if(ha){if(aa){t[v]=y;}else if(ba){t[v]=[];q(t[v],y,w,x+1);}else if(ca){p(da,y,w,x+1);}else !z;}else if(!ea)if(aa){t[v]=y;}else if(ba){t[v]=[];q(t[v],y,w,x+1);}else if(ca){t[v]={};p(t[v],y,w,x+1);}else !z;},s=function(t,u,v){var w=o(u);j(v);p(t,w,v,0);};e.exports=s;});
__d("ArgumentError",["ManagedError"],function(a,b,c,d,e,f,g){function h(i,j){g.prototype.constructor.apply(this,arguments);}h.prototype=new g();h.prototype.constructor=h;e.exports=h;});
__d("CORSRequest",["wrapFunction","QueryString"],function(a,b,c,d,e,f,g,h){function i(l,m){if(!self.XMLHttpRequest)return null;var n=new XMLHttpRequest(),o=function(){};if('withCredentials' in n){n.open(l,m,true);n.setRequestHeader('Content-type','application/x-www-form-urlencoded');}else if(self.XDomainRequest){n=new XDomainRequest();try{n.open(l,m);n.onprogress=n.ontimeout=o;}catch(p){return null;}}else return null;var q={send:function(t){n.send(t);}},r=g(function(){r=o;if('onload' in q)q.onload(n);},'entry','XMLHttpRequest:load'),s=g(function(){s=o;if('onerror' in q)q.onerror(n);},'entry','XMLHttpRequest:error');n.onload=function(){r();};n.onerror=function(){s();};n.onreadystatechange=function(){if(n.readyState==4)if(n.status==200){r();}else s();};return q;}function j(l,m,n,o){n.suppress_http_code=1;var p=h.encode(n);if(m!='post'){l=h.appendToUrl(l,p);p='';}var q=i(m,l);if(!q)return false;q.onload=function(r){o(JSON.parse(r.responseText));};q.onerror=function(r){if(r.responseText){o(JSON.parse(r.responseText));}else o({error:{type:'http',message:'unknown error',status:r.status}});};q.send(p);return true;}var k={execute:j};e.exports=k;});
__d("GlobalCallback",["DOMWrapper","dotAccess","guid","wrapFunction"],function(a,b,c,d,e,f,g,h,i,j){var k,l,m={setPrefix:function(n){k=h(g.getWindow(),n,true);l=n;},create:function(n,o){if(!k)this.setPrefix('__globalCallbacks');var p=i();k[p]=j(n,'entry',o||'GlobalCallback');return l+'.'+p;},remove:function(n){var o=n.substring(l.length+1);delete k[o];}};e.exports=m;});
__d("FlashRequest",["DOMWrapper","Flash","GlobalCallback","QueryString","Queue"],function(a,b,c,d,e,f,g,h,i,j,k){var l,m={},n,o;function p(){if(!n)throw new Error('swfUrl has not been set');var s=i.create(function(){l.start(function(u){var v=o.execute(u.method,u.url,u.body);if(!v)throw new Error('Could create request');m[v]=u.callback;});}),t=i.create(function(u,v,w){var x;try{x=JSON.parse(decodeURIComponent(w));}catch(y){x={error:{type:'SyntaxError',message:y.message,status:v,raw:w}};}m[u](x);delete m[u];});o=h.embed(n,g.getRoot(),null,{log:false,initCallback:s,requestCallback:t});}function q(s,t,u,v){u.suppress_http_code=1;if(!u.method)u.method=t;var w=j.encode(u);if(t==='get'&&s.length+w.length<2000){s=j.appendToUrl(s,w);w='';}else t='post';if(!l){if(!h.isAvailable())return false;l=new k();p();}l.enqueue({method:t,url:s,body:w,callback:v});return true;}var r={setSwfUrl:function(s){n=s;},execute:q};e.exports=r;});
__d("flattenObject",[],function(a,b,c,d,e,f){function g(h){var i={};for(var j in h)if(h.hasOwnProperty(j)){var k=h[j];if(null===k||undefined===k){continue;}else if(typeof k=='string'){i[j]=k;}else i[j]=JSON.stringify(k);}return i;}e.exports=g;});
__d("JSONPRequest",["DOMWrapper","GlobalCallback","QueryString"],function(a,b,c,d,e,f,g,h,i){function j(l,m,n,o){var p=document.createElement('script'),q=function(s){q=function(){};h.remove(n.callback);o(s);p.parentNode.removeChild(p);};n.callback=h.create(q);if(!n.method)n.method=m;l=i.appendToUrl(l,n);if(l.length>2000){h.remove(n.callback);return false;}p.onerror=function(){q({error:{type:'http',message:'unknown error'}});};var r=function(){setTimeout(function(){q({error:{type:'http',message:'unknown error'}});},0);};if(p.addEventListener){p.addEventListener('load',r,false);}else p.onreadystatechange=function(){if(/loaded|complete/.test(this.readyState))r();};p.src=l;g.getRoot().appendChild(p);return true;}var k={execute:j};e.exports=k;});
__d("ObservableMixin",[],function(a,b,c,d,e,f){function g(){this.__observableEvents={};}g.prototype={inform:function(h){var i=Array.prototype.slice.call(arguments,1),j=Array.prototype.slice.call(this.getSubscribers(h));for(var k=0;k<j.length;k++){if(j[k]===null)continue;try{j[k].apply(this,i);}catch(l){setTimeout(function(){throw l;},0);}}return this;},getSubscribers:function(h){return this.__observableEvents[h]||(this.__observableEvents[h]=[]);},clearSubscribers:function(h){if(h)this.__observableEvents[h]=[];return this;},clearAllSubscribers:function(){this.__observableEvents={};return this;},subscribe:function(h,i){var j=this.getSubscribers(h);j.push(i);return this;},unsubscribe:function(h,i){var j=this.getSubscribers(h);for(var k=0;k<j.length;k++)if(j[k]===i){j.splice(k,1);break;}return this;},monitor:function(h,i){if(!i()){var j=function(k){if(i.apply(i,arguments))this.unsubscribe(h,j);}.bind(this);this.subscribe(h,j);}return this;}};e.exports=g;});
__d("sdk.URI",["Assert","QueryString","URIBase"],function(a,b,c,d,e,f,g,h,i){var j=/\.facebook\.com$/,k={serialize:function(o){return o?h.encode(o):'';},deserialize:function(o){return o?h.decode(o):{};}};for(var l in i)if(i.hasOwnProperty(l))n[l]=i[l];var m=i===null?null:i.prototype;n.prototype=Object.create(m);n.prototype.constructor=n;n.__superConstructor__=i;function n(o){"use strict";g.isString(o,'The passed argument was of invalid type.');if(!(this instanceof n))return new n(o);i.call(this,o,k);}n.prototype.isFacebookURI=function(){"use strict";return j.test(this.getDomain());};n.prototype.valueOf=function(){"use strict";return this.toString();};e.exports=n;});
__d("UrlMap",["UrlMapConfig"],function(a,b,c,d,e,f,g){var h={resolve:function(i,j){var k=typeof j=='undefined'?location.protocol.replace(':',''):j?'https':'http';if(i in g)return k+'://'+g[i];if(typeof j=='undefined'&&i+'_'+k in g)return k+'://'+g[i+'_'+k];if(j!==true&&i+'_http' in g)return 'http://'+g[i+'_http'];if(j!==false&&i+'_https' in g)return 'https://'+g[i+'_https'];}};e.exports=h;});
__d("ApiClient",["ArgumentError","Assert","copyProperties","CORSRequest","FlashRequest","flattenObject","JSONPRequest","Log","ObservableMixin","sprintf","sdk.URI","UrlMap","ApiClientConfig"],function(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s){var t,u,v,w={get:true,post:true,'delete':true,put:true},x={fql_query:true,fql_multiquery:true,friends_get:true,notifications_get:true,stream_get:true,users_getinfo:true};function y(da,ea,fa,ga){if(v)fa=i({},v,fa);fa.access_token=fa.access_token||t;fa.pretty=fa.pretty||0;fa=l(fa);var ha={jsonp:m,cors:j,flash:k},ia;if(fa.transport){ia=[fa.transport];delete fa.transport;}else ia=['jsonp','cors','flash'];for(var ja=0;ja<ia.length;ja++){var ka=ha[ia[ja]],la=i({},fa);if(ka.execute(da,ea,la,ga))return;}ga({error:{type:'no-transport',message:'Could not find a usable transport for request'}});}function z(da,ea,fa,ga,ha){ca.inform('request.complete',ea,fa,ga,ha);if(da)da(ha);}function aa(da){h.isString(da,'Invalid path');if(!/^https?/.test(da)&&da.charAt(0)!=='/')da='/'+da;var ea,fa={};try{ea=new q(da);}catch(ga){throw new g(ga.message,ga);}Array.prototype.slice.call(arguments,1).forEach(function(ma){fa[typeof ma]=ma;});var ha=(fa.string||'get').toLowerCase();h.isTrue(w.hasOwnProperty(ha),p('Invalid method passed to ApiClient: %s',ha));var ia=fa['function'];if(!ia)n.warn('No callback passed to the ApiClient');if(fa.object)ea.addQueryData(fa.object);var ja=ea.getQueryData(),ka=z.bind(null,ia,ea.getPath(),ha,ja),la=ea.getProtocol()&&ea.getDomain()?ea.setQueryData({}).toString():r.resolve('graph')+ea.getPath();ja.method=ha;y(la,ha=='get'?'get':'post',ja,ka);}function ba(da,ea){h.isObject(da);h.isString(da.method,'method missing');if(!ea)n.warn('No callback passed to the ApiClient');var fa=da.method.toLowerCase().replace('.','_');da.format='json-strings';da.api_key=u;var ga=fa in x?'api_read':'api',ha=r.resolve(ga)+'/restserver.php',ia=z.bind(null,ea,'/restserver.php','get',da);y(ha,'get',da,ia);}var ca=i(new o(),{setAccessToken:function(da){t=da;},setClientID:function(da){u=da;},setDefaultParams:function(da){v=da;},rest:ba,graph:aa});k.setSwfUrl(s.FlashRequest.swfUrl);e.exports=ca;});