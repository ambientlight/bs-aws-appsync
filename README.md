# bs-aws-appsync
BuckleScript bindings for AWS AppSync client library **(work in progress)**

### Trying out
While work in progress, this package is available at [Github Package Registry](https://github.com/features/packages)

To use the GPR, change the registry for the @amblientlight scope
before installing, in your project directory, run:

```bash
echo "@ambientlight:registry=https://npm.pkg.github.com" >> .npmrc
yarn install @ambientlight/bs-aws-appsync
# if yarn fails with integrity failure, manually add depedency to package.json and run the following
yarn --update-checksums
```

Also add to your `package.json` to lock on correct apollo-client dependency otherwise you may hit [currentObservable.query.getCurrentResult is not a function](https://github.com/apollographql/react-apollo/issues/3148#issuecomment-511622210), this will only work with `yarn` though.

```json
"resolutions": {
  "apollo-client": "2.6.3"
}
```

Then add `@ambientlight/bs-aws-appsync` into `bs-dependencies` in your project `bsconfig.json`.

### Example usage with bs-aws-amplify(with cognito-identity-pool auth)
1. refer to [bs-aws-amplify](https://github.com/ambientlight/bs-aws-amplify) installation.
2. make sure AWSExports.re is available that binds `aws-exports.js` that is generated during `amplify init` or `amplify configure`

```reason
open AWSAppSync;
open AWSAmplify;

/** AWSAmplify has to be configured prior */
// Amplify.amplify |. Amplify.configure(AWSExports.config);

let auth = AWSAppSyncClient.auth(
  ~_type=AWSExports.config |. AWSExports.aws_appsync_authenticationTypeGet,
  ~jwtToken=() => 
    /**uncomment and fill creds if no cognito authentification in place */
    // Auth.signIn(~username="", ~password="") |> Js.Promise.then_(_signIn => Auth.auth |. Auth.currentSession)
    Auth.auth |. Auth.currentSession
    |> Js.Promise.then_(currentSession => {
      //Js.log(currentSession);
      currentSession 
      |. CognitoUserSession.getAccessToken
      |. CognitoAccessToken.getJwtToken
      |> Js.Promise.resolve
    })
);

let client = AWSAppSyncClient.create(~options=AWSAppSyncClient.createOptions(
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
