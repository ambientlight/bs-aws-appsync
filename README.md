# bs-aws-appsync
BuckleScript bindings for AWS AppSync client library **(work in progress)**

### Trying out
While work in progress, this package is available at [Github Package Registry](https://github.com/features/packages)

To use the GPR, change the registry for the @amblientlight scope
before installing, in your project directory, run:

```bash
echo "@ambientlight:registry=https://npm.pkg.github.com" >> .npmrc
npm install @ambientlight/bs-aws-appsync
```

Then add `@ambientlight/bs-aws-appsync` into `bs-dependencies` in your project `bsconfig.json`.

### Example usage with bs-aws-amplify(with cognito-identity-pool auth)
1. refer to bs-aws-amplify installation.
2. make sure AWSExports.re is available that binds `aws-exports.js` that is generated during `amplify init` or `amplify configure`

```reason
/** AWSAmplify has to be configured prior */
// AWSAmplify.amplify |. AWSAmplify.Amplify.configure(AWSExports.config);

let auth = AWSAppSync.AWSAppSyncClient.auth(
  ~_type=AWSExports.config |. AWSExports.aws_appsync_authenticationTypeGet,
  ~jwtToken=() => 
    /** uncomment and fill creds if no cognito authentification in place */
    // AWSAmplify.Auth.signIn(~username="", ~password="") |> Js.Promise.then_(_signIn => AWSAmplify.auth |. AWSAmplify.Auth.currentSession)
    AWSAmplify.auth |. AWSAmplify.Auth.currentSession
    |> Js.Promise.then_(currentSession => {
      currentSession 
      |. AWSAmplify.CognitoUserSession.getAccessToken
      |. AWSAmplify.CognitoAccessToken.getJwtToken
      |> Js.Promise.resolve
    })
);

let client = AWSAppSync.AWSAppSyncClient.create(~options=AWSAppSync.AWSAppSyncClient.createOptions(
  ~url=AWSExports.config |. AWSExports.aws_appsync_graphqlEndpointGet,
  ~region=AWSExports.config |. AWSExports.aws_appsync_regionGet,
  ~auth,
  ~disableOffline=true,
  ()
), ());

```

3. further follow [react-apollo-hooks](https://github.com/Astrocoders/reason-apollo-hooks) installation guide with above client used in

```reason
let app =
 <ReasonApolloHooks.ApolloProvider client>
   ...
 </ReasonApolloHooks.ApolloProvider>
```