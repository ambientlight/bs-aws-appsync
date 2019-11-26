type t = ApolloClient.generatedApolloClient;

[@bs.deriving abstract]
type auth = {
  [@bs.as "type"] _type: string,
  jwtToken: unit => Js.Promise.t(string) 
};

[@bs.obj] external createOptions: (
  ~url: string=?,
  ~region: string=?,
  ~disableOffline: bool=?,
  ~auth: auth=?,
  unit
) => _ = "";

[@bs.module "aws-appsync"][@bs.new]
external _create: (~options: 'a=?, unit) => t = "AWSAppSyncClient";

let create = (~options=createOptions(()), ()) => _create(~options, ());