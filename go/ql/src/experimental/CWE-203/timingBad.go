func bad(w http.ResponseWriter, req *http.Request, []byte secret) (interface{}, error) {

	secretHeader := "X-Secret"

	headerSecret := req.Header.Get(secretHeader)
	secretStr := string(secret)
	if len(secret) != 0 && headerSecret != secretStr {
		return nil, fmt.Errorf("header %s=%s did not match expected secret", secretHeader, headerSecret)
	}
	return nil, nil
}